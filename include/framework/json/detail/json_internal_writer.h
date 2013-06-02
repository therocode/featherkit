//
// json0
//
// 2011 Michael Nicolella
//

#ifndef JSON0_JSON_INTERNAL_WRITER_H
#define JSON0_JSON_INTERNAL_WRITER_H

#include <string>
#include <ios>
#include <iostream>

#include <json/json_value.h>

namespace json
{
  namespace detail
  {
    namespace json_detail
    {
      static char const* kIndentStr = "  ";
    }

    inline void indent_str( std::ostream& out, std::size_t indent )
    {
      while( indent-- )
      {
        out << json_detail::kIndentStr;
      }
    }

    inline void json_write_impl(std::ostream& out, json::Value const& node, std::size_t indent)
    {
      using namespace json;

      switch(node.type)
      {

      case kValueString:
        {
          out << std::string("\"") << node.GetString() << std::string("\"");
        }
        break;

      case kValueInt:
        {
          out << std::to_string(node.GetInt());
        }
        break;

      case kValueFloat:
        {
          std::ios_base::fmtflags flags = out.flags();

          out << std::showpoint;
          out << node.GetFloat();

          out.setf(flags);
        }
        break;

      case kValueObject:
        {
          out << "{\n";

          std::size_t numMembers = node.GetNumMembers();

          for( std::size_t memberIdx = 0; memberIdx < numMembers; ++memberIdx )
          {
            Member const& member = node.GetMember(memberIdx);
            
            indent_str(out, indent+1);

            if( memberIdx != 0 ) out << ",";
            else                 out << " ";

            out << '"' << member.name << "\" : ";

            if( member.value.type == kValueObject )
            {
              out << '\n';
              indent_str(out, indent+2);
            }

            json_write_impl( out, member.value, indent+2 );

            out << '\n';
          }

          indent_str(out, indent);
          out << "}\n";


        }
        break;

      case kValueArray:
        {
          std::pair<bool, ValueType> arrayInfo = node.IsHomogenousArray();

          bool arrayOfObjects = (arrayInfo.first && arrayInfo.second == kValueObject);

          if( arrayOfObjects )
          {
            //special formatting for this case
            out << '\n';
            indent_str(out, indent);
            out << "[\n";

            std::size_t numElements = node.GetNumElements();

            for( std::size_t e = 0; e < numElements; ++e )
            {
              indent_str(out, indent+1);

              if( e > 0 ) out << ", ";
              else        out << "  ";

              json_write_impl( out, node.GetElement(e), indent+2 );
            }

            indent_str(out, indent);
            out << "]\n";
          }
          else
          {
            out << '[';

            std::size_t numElements = node.GetNumElements();
            for( std::size_t e = 0; e < numElements; ++e )
            {
              if( e > 0 ) out << ", ";
              else        out << " ";

              json_write_impl( out, node.GetElement(e), indent+2 );
            }

            out << " ]";
          }

        }
        break;

      case kValueBool:
        {
          if( node.GetBool() ) out << "true";
          else                 out << "false";
        }
        break;

      case kValueNull:
        {
          out << "null";
        }
        break;
      }
    }

  }
}


#endif
