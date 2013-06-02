//
// json0
//
// 2011 Michael Nicolella
//

#ifndef JSON0_JSON_WRITER_H
#define JSON0_JSON_WRITER_H

#include <framework/json/json_value.h>

#include <framework/json/detail/json_internal.h>
#include <framework/json/detail/json_internal_writer.h>

#include <ostream>

namespace json
{
  inline void write( std::ostream& out, json::Value& root )
  {
    //root element must be Object
    if( root.type == kValueObject )
    {
      detail::json_write_impl(out, root, 0);
    }
    else
    {
      detail::RaiseException("root object passed to json::write must be an Object");
    }
  }
}

#endif
