//
// json0
//
// 2011 Michael Nicolella
//

#ifndef JSON0_JSON_INTERNAL_H
#define JSON0_JSON_INTERNAL_H

#include <string>
#include <vector>
#include <stdexcept>

#include <fea/json/json_config.h>


#define jsonInternalAssert(Expression) json::detail::InternalAssert( Expression, #Expression )

namespace json
{
  struct Value;
  struct Member;

  struct JsonException : std::runtime_error
  {
    explicit JsonException(std::string const& message)
      :std::runtime_error(message)
    {
    }

    explicit JsonException(char const* message)
      :std::runtime_error(message)
    {
    }
  };


  namespace detail
  {

    template<typename T>
    void unused_arg( T const& t )
    {
      (void)t;
    }

    inline void RaiseException( std::string const& message )
    {
      throw json::JsonException(message);
    }


    inline void InternalAssert( bool condition, char const* expressionStr )
    {
      if( !condition )
      {
        RaiseException(expressionStr);
      }
    }


    struct ValueString
    {
      std::string data;

      ValueString() {}
      ValueString( ValueString const& rhs ):data(rhs.data){}
      ValueString( ValueString&& rhs      ):data(std::move(rhs.data)){}

      ValueString& operator=( ValueString const& rhs ){data = rhs.data;return *this;}
      ValueString& operator=( ValueString&& rhs      ){data = std::move(rhs.data);return *this;}

      template<typename StringT>
      ValueString( StringT&& d, typename std::enable_if< !std::is_same<StringT,ValueString&>::value >::type* = 0 )
        :data(std::forward<StringT>(d))
      {
      }
    };

    struct ValueInt
    {
      json::int_t data;
    };

    struct ValueFloat
    {
      json::float_t data;
    };

    struct ValueBool
    {
      bool data;
    };

    struct ValueArray
    {
      std::vector<Value> elements;

      ValueArray(){}
      ValueArray( ValueArray const& rhs ):elements(rhs.elements){}
      ValueArray( ValueArray&& rhs      ):elements(std::move(rhs.elements)){}

      ValueArray& operator=( ValueArray const& rhs )
      {
        elements = rhs.elements;
        return *this;
      }

      ValueArray& operator=( ValueArray&& rhs )
      {
        elements = std::move(rhs.elements);
        return *this;
      }
    };

    struct ValueObject
    {
      std::vector<json::Member> members;

      ValueObject(){}
      ValueObject( ValueObject const& rhs ):members(rhs.members){}
      ValueObject( ValueObject&& rhs      ):members(std::move(rhs.members)){}

      ValueObject& operator=( ValueObject const& rhs )
      {
        members = rhs.members;
        return *this;
      }

      ValueObject& operator=( ValueObject&& rhs )
      {
        members = std::move(rhs.members);
        return *this;
      }
    };


    template<std::size_t Lhs, std::size_t Rhs>
    struct max_
    {
      static std::size_t const value = Lhs > Rhs ? Lhs : Rhs;
    };


    struct find_largest_value_size
    {
      static std::size_t const value = max_<sizeof(ValueString)
                                      ,max_<sizeof(ValueInt)
                                      ,max_<sizeof(ValueFloat)
                                      ,max_<sizeof(ValueBool)
                                      ,max_<sizeof(ValueArray),sizeof(ValueObject)
                                      >::value
                                      >::value
                                      >::value
                                      >::value
                                    >::value;
    };


  }
}

#endif
