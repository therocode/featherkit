//
// json0
//
// 2011 Michael Nicolella
//

#ifndef JSON0_JSON_READER_H
#define JSON0_JSON_READER_H

#include <string>

#include <fea/json/json_value.h>

#include <fea/json/detail/json_internal_tokenizer.h>
#include <fea/json/detail/json_internal_parser.h>

#include <istream>
#include <iostream>
#include <iterator>

namespace json
{
  inline void read( std::vector<char> const& in, json::Value& root )
  {
    detail::TokenizerResult tokenizerResult;
    
    detail::Tokenize(in, tokenizerResult);

    if( tokenizerResult.fault )
    {
      detail::RaiseException("Error tokenizing: " + tokenizerResult.faultMsg);
    }

    detail::ParserResult parserResult = detail::Parse( in, tokenizerResult.tokens, root );

    if( parserResult.fault )
    {
      detail::RaiseException("Error parsing: " + parserResult.faultMsg);
    }
  }

  inline void read( std::istream& in, json::Value& root )
  {
    in >> std::noskipws;

    std::vector<char> const inBuff( std::istream_iterator<char>(in), (std::istream_iterator<char>()) );
    read( inBuff, root );
  }
}

#endif
