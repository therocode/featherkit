//
// json0
//
// 2011 Michael Nicolella
//

#ifndef JSON0_JSON_INTERNAL_TOKENIZER_H
#define JSON0_JSON_INTERNAL_TOKENIZER_H

#include <sstream>
#include <vector>
#include <deque>
#include <iomanip>

namespace json
{
  namespace detail
  {
    enum TokenType
    {
      kTokInvalid
      ,kTokString
      ,kTokNumber
      ,kTokOpenBrace    // {
      ,kTokCloseBrace   // }
      ,kTokColon        // :
      ,kTokOpenBracket  // [
      ,kTokCloseBracket // ]
      ,kTokComma        // ,
      ,kTokTrue         // true
      ,kTokFalse        // false
      ,kTokNull         // null
    };

    inline char const* TokenToString( TokenType type )
    {
      switch( type )
      {
      case kTokInvalid      : return "--kTokInvalid--";
      case kTokString       : return "kTokString";
      case kTokNumber       : return "kTokNumber";
      case kTokOpenBrace    : return "kTokOpenBrace";
      case kTokCloseBrace   : return "kTokCloseBrace";
      case kTokColon        : return "kTokColon";
      case kTokOpenBracket  : return "kTokOpenBracket";
      case kTokCloseBracket : return "kTokCloseBracket";
      case kTokComma        : return "kTokComma";
      case kTokTrue         : return "kTokTrue";
      case kTokFalse        : return "kTokFalse";
      case kTokNull         : return "kTokNull";
      }

      return "<invalid>";
    }


    inline bool TokenHasSymbol( TokenType type )
    {
      switch(type)
      {
      case kTokString:
      case kTokNumber:
        return true;

      default:
        return false;
      }
    }


    struct Token
    {
      TokenType   type;

      std::size_t textBeginIndex;
      std::size_t textLength;

      std::size_t row;
      std::size_t col;

      Token()
      {
        Reset();
      }

      void Reset()
      {
        textBeginIndex = 0;
        textLength = 0;

        row=0;
        col=0;

        type = kTokInvalid;
      }

      std::string GetText( std::vector<char> const& src ) const
      {
        if( textLength > 0 )
        {
          char const* begin( &src[textBeginIndex] );
          return std::string( begin, begin+textLength );
        }
        else
        {
          return std::string();
        }
      }
    };

    typedef std::vector<Token> TokenContainerT;


    struct TokenizerResult
    {
      TokenContainerT tokens;
      bool fault;
      std::string faultMsg;
    };

    void Tokenize( std::vector<char> const& in, TokenizerResult& result );


    struct TokenizerException : std::runtime_error
    {
      explicit TokenizerException(std::string const& message)
        :std::runtime_error(message)
      {
      }

      explicit TokenizerException(char const* message)
        :std::runtime_error(message)
      {
      }
    };

    inline void RaiseTokenizerException( std::size_t row, std::size_t col, char const* message )
    {
      std::stringstream ss;

      ss << "[row: " << row << "][col: " << col << "] : " << message;

      throw TokenizerException( ss.str() );
    }

    struct Tokenizer
    {
      std::vector<char> const& src;
      std::size_t srcCursor;

      TokenContainerT& tokens;

      bool use_char;
      char ch;

      Token token;

      std::size_t row;
      std::size_t col;

      Tokenizer(std::vector<char> const& in, TokenContainerT& tokens)
        :src(in)
        ,srcCursor(0)
        ,tokens(tokens)
      {
      }

      void Fault( std::string const& message )
      {
        Fault( message.c_str() );
      }

      void Fault( char const* message )
      {
        RaiseTokenizerException(row, col-1, message);
      }

      void Tokenize()
      {
        row = 1;
        col = 1;

        use_char = false;

        for(;;)
        {
          if( use_char && IsWhiteSpace(ch) )
          {
            use_char = false;
          }

          if( use_char || GetChar_SkipWS() )
          {
            use_char = false;

            token.row = row;
            token.col = col-1;

            if     ( ch == '{' ) { token.type = kTokOpenBrace; }
            else if( ch == '}' ) { token.type = kTokCloseBrace; }

            else if( ch == '[' ) { token.type = kTokOpenBracket; }
            else if( ch == ']' ) { token.type = kTokCloseBracket; }

            else if( ch == ':' ) { token.type = kTokColon; }
            else if( ch == ',' ) { token.type = kTokComma; }

            else if( ch == '"' ) { ParseString(); }

            else if( ch == '-' || isdigit(ch) ) { ParseNumber(); }

            else if( ch == 't' ) { ParseConstString("true");  token.type = kTokTrue; }
            else if( ch == 'f' ) { ParseConstString("false"); token.type = kTokFalse; }

            else if( ch == 'n' ) { ParseConstString("null");  token.type = kTokNull; }


            if( token.type == kTokInvalid )
            {
              if( isprint(ch) )
              {
                Fault( std::string("Unrecognized character '") + ch + "'" );
              }
              else
              {
                Fault( std::string("Non-printable character. Binary data?" ) );
              }
            }

            tokens.push_back(token);
            token.Reset();
          }
          else
          {
            return;
          }
        }
      }


      void ParseConstString( std::string const& str )
      {
        std::string s;
        s += ch;

        for(;;)
        {
          //if we're good so far
          int result = str.compare(0, s.size(), s );

          if( result == 0 )
          {
            //are we done?
            if( s.size() == str.size() ) break;

            if( GetChar() )
            {
              s += ch;
            }
            else
            {
              Fault( "Expected string: " + str + ", got EOF" );
            }
          }
          else
          {
            Fault( "Expected string: " + str );
          }
        }
      }

      bool IsWhiteSpace( char ch )
      {
        if( ch == '\n' || ch == '\r' || ch == '\t' || ch == ' ' )
        {
          return true;
        }

        return false;
      }

      void ParseNumber()
      {
        std::size_t numStart = srcCursor-1;
        std::size_t numLen = 1;

        while(GetChar())
        {
          if( isdigit(ch)
            || ch == '+'
            || ch == '-'
            || ch == '.'
            || ch == 'e'
            || ch == 'E'
            )
          {
            ++numLen;
          }
          else
          {
            use_char = true;
            break;
          }
        }

        token.type = kTokNumber;
        token.textBeginIndex = numStart;
        token.textLength = numLen;
      }


      void ParseString()
      {
        std::size_t strBegin = srcCursor;
        std::size_t strLen   = 0;

        while(GetChar())
        {
          if( ch == '"' )
          {
            //end of string
            break;
          }
          else
          {
            ++strLen;
          }
        }

        token.type = kTokString;
        token.textBeginIndex = strBegin;
        token.textLength = strLen;
      }

      bool GetChar()
      {
        if( srcCursor < src.size() )
        {
          ch = src[srcCursor];
          ++srcCursor;

          ++col;

          if( ch == '\n' )
          {
            ++row;
            col = 1;
          }

          return true;
        }

        return false;
      }

      bool GetChar_SkipWS()
      {
        while(GetChar())
        {
          if( IsWhiteSpace(ch) ) continue;
          return true;
        }

        return false;
      }

    private:
      Tokenizer( Tokenizer const& );
      Tokenizer& operator=( Tokenizer const& );
    };

    inline void Tokenize( std::vector<char> const& in, TokenizerResult& result )
    {
      try
      {
        Tokenizer tokenizer(in, result.tokens);
        tokenizer.Tokenize();

        result.tokens = tokenizer.tokens;
        result.fault = false;
      }
      catch( TokenizerException const& e )
      {
        result.fault = true;
        result.faultMsg = e.what();
      }
    }
  }
}


#endif
