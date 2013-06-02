//
// json0
//
// 2011 Michael Nicolella
//

#ifndef JSON0_JSON_INTERNAL_PARSER_H
#define JSON0_JSON_INTERNAL_PARSER_H

#include <framework/json/json_config.h>
#include <framework/json/json_value.h>
#include <framework/json/detail/json_internal_tokenizer.h>

#include <string>
#include <stdexcept>
#include <vector>

namespace json
{
  namespace detail
  {

    struct ParserResult
    {
      bool fault;
      std::string faultMsg;
    };


    struct ParserException : std::runtime_error
    {
      explicit ParserException(std::string const& message)
        :std::runtime_error(message)
      {
      }

      explicit ParserException(char const* message)
        :std::runtime_error(message)
      {
      }
    };

    inline void RaiseParserException( std::vector<char> const& src, Token const* token, char const* message )
    {
      std::stringstream ss;

      if( token )
      {
        ss << "[row: " << token->row << "][col: " << token->col << "][token type '" << token->type << "']";

        if( TokenHasSymbol(token->type) )
        {
          ss << "[text: " << token->GetText(src) << ']';
        }
      }

      ss << " : " << message;

      throw ParserException( ss.str() );
    }



    struct Parser
    {
      std::vector<char> const& src;
      TokenContainerT& tokens;

      Token* token;

      std::size_t pos;
      bool cur_token;


      Parser( std::vector<char> const& src, TokenContainerT& tokens )
        :src(src)
        ,tokens(tokens)
        ,token(nullptr)
      {
      }

      void Fault( std::string const& message )
      {
        Fault(message.c_str());
      }

      void Fault( char const* message )
      {
        RaiseParserException( src, token, message );
      }

      void Fault( Token const* token, std::string const& message )
      {
        Fault(token, message.c_str());
      }

      void Fault( Token const* token, char const* message )
      {
        RaiseParserException( src, token, message );
      }


      void Parse( Value& root )
      {
        if( tokens.empty() )
        {
          Fault( "No tokens in stream" );
        }

        cur_token = false;
        pos = 0;

        //root should be an object
        ParseObject(root);
      }

      bool NextToken()
      {
        if( cur_token )
        {
          cur_token = false;
          return true;
        }

        if( pos < tokens.size() )
        {
          token = &tokens[pos];
          ++pos;
          return true;
        }

        return false;
      }

      bool ExpectTokenType(TokenType type)
      {
        if( NextToken() && token->type == type ) return true;

        return false;
      }

      void ParseObject( Value& obj )
      {
        if( !ExpectTokenType(kTokOpenBrace) ){ Fault("Expected start-of-object"); }

        obj.SetObject();

        ParseObjectMembers(obj);

        if( !ExpectTokenType(kTokCloseBrace) ) { Fault("Expected end-of-object"); }
      }

      void PrefetchTokens( std::size_t num, std::vector<Token const*>& result )
      {
        while( num-- )
        {
          if( NextToken() )
          {
            result.push_back(token);
          }
        }
      }

      void ParseValue( Value& val )
      {
        //figure out what this is

        if( NextToken() )
        {

          switch( token->type )
          {
          case kTokString:
            {
              val.SetString(std::move(token->GetText(src)));
            }
            break;

          case kTokNumber:
            {
              cur_token = true;
              ParseNumber(val);
            }
            break;

          case kTokOpenBrace:
            {
              cur_token = true;
              ParseObject(val);
            }
            break;

          case kTokOpenBracket:
            {
              cur_token = true;
              ParseArray( val );
            }
            break;

          case kTokTrue:
            {
              val.SetBool(true);
            }
            break;

          case kTokFalse:
            {
              val.SetBool(false);
            }
            break;
          case kTokNull:
            {
              val.SetNull();
            }
            break;
          default:
            {
            }


          case kTokCloseBrace:
          case kTokColon:
          case kTokCloseBracket:
          case kTokComma:
            //bad!
            Fault("Expected value");
            break;
          }

        }
      }

      void ParseArray( Value& arr )
      {
        if( !ExpectTokenType(kTokOpenBracket) ){ Fault("Expected start-of-array"); }

        arr.SetArray();

        ParseArrayElements(arr);

        if( !ExpectTokenType(kTokCloseBracket) ){ Fault("Expected end-of-array"); }
      }

      void ParseArrayElements( Value& arr )
      {
        for(;;)
        {
          if( NextToken() )
          {
            cur_token = true;

            if( token->type == kTokCloseBracket ) //empty array?
            {
              return;
            }
          }
          else
          {
            Fault("Expected array elements, got EOF ");
          }

          Value element;
          ParseValue(element);

          arr.AddValue(element);

          if( NextToken() )
          {
            if( token->type == kTokComma )
            {
              continue;
            }
            else if( token->type == kTokCloseBracket )
            {
              cur_token = true;
              return;
            }
            else
            {
              Fault("Parsing array elements, expected comma or end-of-array");
              return;
            }
          }
          else
          {
            Fault("Parsing array elements, unexpected EOF ");
            return;
          }

        }
      }

      void ParseNumber( Value& num )
      {
        //figure out if it's an int or float
        if( NextToken() && token->type == kTokNumber )
        {
          std::string text = token->GetText(src);
          bool isfloat = (text.find('.') != std::string::npos);

          std::stringstream ss( std::move(text) );

          if( isfloat )
          {
            //float
            json::float_t f = 0;

            if( ss >> f )
            {
              num.SetFloat( f );
            }
            else
            {
              Fault("Expected float");
            }
          }
          else
          {
            //int
            json::int_t i = 0;

            if( ss >> i )
            {
              num.SetInt( i );
            }
            else
            {
              Fault("Expected int");
            }
          }
        }
        else
        {
          Fault("Expected number, got EOF");
        }
      }

      void ParseObjectMembers( Value& obj )
      {
        for(;;)
        {

          //check for empty object
          if( NextToken() )
          {
            cur_token = true;

            if( token->type == kTokCloseBrace ) //empty object
            {
              return;
            }
          }
          else
          {
            Fault("Expected object member or end of object, got EOF");
          }

          std::vector<Token const*> prefetch;
          PrefetchTokens( 3, prefetch ); // string : value

          if( prefetch.size() == 1 )
          {
            //this is OK, if we hit a close brace (end of object)
            if( prefetch[0]->type == kTokCloseBrace )
            {
              cur_token = true;
            }
            else
            {
              Fault("Expected object member, got EOF");
            }

            return;
          }

          if( prefetch.size() != 3 )
          {
            Fault("Expected object member, got EOF");
            return;
          }

          if( prefetch[0]->type != kTokString )
          {
            Fault( prefetch[0], "Parsing object member, expected member name string");
          }

          if( prefetch[1]->type != kTokColon )
          {
            Fault( prefetch[1], "Parsing object member, expected colon separator");
          }


          Value memberValue;

          cur_token = true;
          ParseValue( memberValue );

          obj.SetValueMember( prefetch[0]->GetText(src), memberValue );

          if( NextToken() && token->type == kTokComma )
          {
            continue;
          }
          else
          {
            //end of the line
            cur_token = true;
            return;
          }
        }
      }

      private:
        Parser( Parser const& );
        Parser& operator=( Parser const& );
    };


    inline ParserResult Parse( std::vector<char> const& src, TokenContainerT& tokens, Value& root )
    {
      ParserResult result;

      try
      {
        Parser parser(src, tokens);
        parser.Parse( root );

        result.fault = false;

      }
      catch( ParserException const& e )
      {
        result.fault = true;
        result.faultMsg = e.what();
      }

      return result;
    }

  }
}

#endif
