//
// json0
//
// 2011 Michael Nicolella
//

#ifndef JSON0_JSON_VALUE_H
#define JSON0_JSON_VALUE_H

#include <string>
#include <vector>
#include <map>

#include <featherkit/json/json_config.h>
#include <featherkit/json/detail/json_internal.h>

namespace json
{
  enum ValueType
  {
    kValueNull
    ,kValueString
    ,kValueInt
    ,kValueFloat
    ,kValueBool
    ,kValueArray
    ,kValueObject
  };


  struct Value
  {
    char data[detail::find_largest_value_size::value];
    ValueType type;

    Value()
      :type(kValueNull)
    {
    }

    Value( Value const& rhs )
      :type(kValueNull)
    {
      *this = rhs;
    }

    Value( Value&& rhs )
      :type(kValueNull)
    {
      *this = std::move(rhs);
    }

    Value& operator=( Value const& rhs )
    {
      switch(rhs.type)
      {
      case kValueString: *InternalMakeString() = *rhs.InternalGetString(); break;
      case kValueInt:    *InternalMakeInt()    = *rhs.InternalGetInt();    break;
      case kValueFloat:  *InternalMakeFloat()  = *rhs.InternalGetFloat();  break;
      case kValueObject: *InternalMakeObject() = *rhs.InternalGetObject(); break;
      case kValueArray:  *InternalMakeArray()  = *rhs.InternalGetArray();  break;
      case kValueBool:   *InternalMakeBool()   = *rhs.InternalGetBool();   break;
      case kValueNull:   InternalMakeNull();                               break;
      }
      return *this;
    }

    Value& operator=( Value&& rhs )
    {
      DestructValue(type,data);

      type = rhs.type;

      switch(type)
      {
      case kValueString: InternalMoveString(std::move(*rhs.InternalGetString())); break;
      case kValueInt:    InternalMoveInt   (std::move(*rhs.InternalGetInt()));    break;
      case kValueFloat:  InternalMoveFloat (std::move(*rhs.InternalGetFloat()));  break;
      case kValueObject: InternalMoveObject(std::move(*rhs.InternalGetObject())); break;
      case kValueArray:  InternalMoveArray (std::move(*rhs.InternalGetArray()));  break;
      case kValueBool:   InternalMoveBool  (std::move(*rhs.InternalGetBool()));   break;
      case kValueNull:   InternalMakeNull();                                      break;
      }

      return *this;
    }

    ~Value()
    {
      DestructValue(type,data);
    }



    inline bool IsNull()   const { return type == kValueNull;   }
    inline bool IsString() const { return type == kValueString; }
    inline bool IsInt()    const { return type == kValueInt;    }
    inline bool IsFloat()  const { return type == kValueFloat;  }
    inline bool IsBool()   const { return type == kValueBool;   }
    inline bool IsArray()  const { return type == kValueArray;  }
    inline bool IsObject() const { return type == kValueObject; }


    //
    // standard value
    //

    void SetNull  ()                           { InternalMakeNull();                 }
    void SetInt   ( json::int_t value )        { InternalMakeInt()->data = value;    }
    void SetFloat ( json::float_t value )      { InternalMakeFloat()->data = value;  }
    void SetBool  ( bool value )               { InternalMakeBool()->data = value;   }
    void SetArray ()                           { InternalMakeArray();                }
    void SetObject()                           { InternalMakeObject();               }
    template<typename StringT>
    void SetString( StringT&& value )          { InternalMakeString(std::forward<StringT>(value)); }

    std::string const& GetString() const { return InternalGetString()->data; }
    json::int_t        GetInt()    const { return InternalGetInt()->data;    }
    json::float_t      GetFloat()  const { return InternalGetFloat()->data;  }
    bool               GetBool()   const { return InternalGetBool()->data;   }


    //
    // Object accessors
    //

    template<typename StringT> void SetValueMember ( StringT&& member, Value const& value )       { GetOrAddMember(std::forward<StringT>(member), value); }
    template<typename StringT> void SetValueMember ( StringT&& member, Value&&      value )       { GetOrAddMember(std::forward<StringT>(member), std::move(value)); }
    template<typename StringT> void SetNullMember  ( StringT&& member )                           { GetOrAddMember(std::forward<StringT>(member)).SetNull(); }
    template<typename StringT, typename StringValueT> void SetStringMember( StringT&& member, StringValueT&& value ) { GetOrAddMember(std::forward<StringT>(member)).SetString(std::forward<StringValueT>(value)); }
    template<typename StringT> void SetIntMember   ( StringT&& member, json::int_t value )        { GetOrAddMember(std::forward<StringT>(member)).SetInt(value); }
    template<typename StringT> void SetFloatMember ( StringT&& member, json::float_t value )      { GetOrAddMember(std::forward<StringT>(member)).SetFloat(value); }
    template<typename StringT> void SetBoolMember  ( StringT&& member, bool value )               { GetOrAddMember(std::forward<StringT>(member)).SetBool(value); }
    template<typename StringT> void SetArrayMember ( StringT&& member, Value const& value )       { GetOrAddMember(std::forward<StringT>(member)) = value; }
    template<typename StringT> void SetObjectMember( StringT&& member, Value const& value )       { GetOrAddMember(std::forward<StringT>(member)) = value; }

    template<typename StringT> std::string const& GetStringMember ( StringT&& memberName ) const { return GetMemberValue(std::forward<StringT>(memberName))->GetString(); }
    template<typename StringT> json::int_t        GetIntMember    ( StringT&& memberName ) const { return GetMemberValue(std::forward<StringT>(memberName))->GetInt(); }
    template<typename StringT> json::float_t      GetFloatMember  ( StringT&& memberName ) const { return GetMemberValue(std::forward<StringT>(memberName))->GetFloat(); }
    template<typename StringT> bool               GetBoolMember   ( StringT&& memberName ) const { return GetMemberValue(std::forward<StringT>(memberName))->GetBool(); }

    template<typename StringT> Value&             GetArrayMember  ( StringT&& memberName )       { return *GetMemberValue(std::forward<StringT>(memberName)); }
    template<typename StringT> Value const&       GetArrayMember  ( StringT&& memberName ) const { return *GetMemberValue(std::forward<StringT>(memberName)); }

    template<typename StringT> Value&             GetObjectMember ( StringT&& memberName )       { return *GetMemberValue(std::forward<StringT>(memberName)); }
    template<typename StringT> Value const&       GetObjectMember ( StringT&& memberName ) const { return *GetMemberValue(std::forward<StringT>(memberName)); }

    std::size_t GetNumMembers() const { return InternalGetObject()->members.size(); }

    Member const& GetMember( std::size_t index ) const { return InternalGetObject()->members[index]; }

    template<typename StringT> bool HasMember( StringT&& memberName ) const;


    //
    // Array accessors
    //

    void AddNull  ()                           { Value v; v.SetNull();        InternalGetArray()->elements.push_back(std::move(v)); }

    template<typename StringT>
    void AddString( StringT&& value ) { Value v; v.SetString(std::forward<StringT>(value)); InternalGetArray()->elements.push_back(std::move(v)); }

    void AddInt   ( json::int_t value )        { Value v; v.SetInt(value);    InternalGetArray()->elements.push_back(std::move(v)); }
    void AddFloat ( json::float_t value )      { Value v; v.SetFloat(value);  InternalGetArray()->elements.push_back(std::move(v)); }
    void AddBool  ( bool value )               { Value v; v.SetBool(value);   InternalGetArray()->elements.push_back(std::move(v)); }
    void AddArray ( Value const& value )       { InternalGetArray()->elements.push_back(value); }
    void AddObject( Value const& value )       { InternalGetArray()->elements.push_back(value); }
    void AddValue ( Value const& value )       { InternalGetArray()->elements.push_back(value); }

    std::size_t  GetNumElements() const { return InternalGetArray()->elements.size(); }

    Value&       GetElement( std::size_t index )       { return InternalGetArray()->elements[index]; }
    Value const& GetElement( std::size_t index ) const { return InternalGetArray()->elements[index]; }

    void DelElement( std::size_t index )
    {
      detail::ValueArray* array = InternalGetArray();
      std::vector<Value>::iterator where = array->elements.begin();
      std::advance(where, (int32_t)index);
      array->elements.erase(where);
    }

    //is every value in this array of the same type?
    std::pair<bool, ValueType> IsHomogenousArray() const
    {
      std::pair<bool, ValueType> result;

      detail::ValueArray const* array = InternalGetArray();

      if( array->elements.empty() )
      {
        return std::make_pair(true, kValueNull);
      }

      ValueType t = array->elements[0].type;

      for( std::vector<Value>::const_iterator iter = array->elements.begin(); iter != array->elements.end(); ++iter )
      {
        if( iter->type != t )
        {
          result.first = false;
          return result;
        }
      }

      result.first  = true;
      result.second = t;

      return result;
    }



  private:
    inline void*                InternalMakeNull()   { DestructValue(type,data); type = kValueNull;   return 0; }
    template<typename StringT>
    inline detail::ValueString* InternalMakeString(StringT&& value) { DestructValue(type,data); type = kValueString; return new (data) detail::ValueString(std::forward<StringT>(value)); }
    inline detail::ValueString* InternalMakeString() { DestructValue(type,data); type = kValueString; return new (data) detail::ValueString; }
    inline detail::ValueInt*    InternalMakeInt()    { DestructValue(type,data); type = kValueInt;    return new (data) detail::ValueInt;    }
    inline detail::ValueFloat*  InternalMakeFloat()  { DestructValue(type,data); type = kValueFloat;  return new (data) detail::ValueFloat;  }
    inline detail::ValueBool*   InternalMakeBool()   { DestructValue(type,data); type = kValueBool;   return new (data) detail::ValueBool;   }
    inline detail::ValueArray*  InternalMakeArray()  { DestructValue(type,data); type = kValueArray;  return new (data) detail::ValueArray;  }
    inline detail::ValueObject* InternalMakeObject() { DestructValue(type,data); type = kValueObject; return new (data) detail::ValueObject; }

    inline void*                InternalMoveNull()                            { type = kValueNull;   return 0; }
    inline detail::ValueString* InternalMoveString(detail::ValueString&& rhs) { type = kValueString; return new (data) detail::ValueString(std::move(rhs)); }
    inline detail::ValueInt*    InternalMoveInt   (detail::ValueInt&& rhs)    { type = kValueInt;    return new (data) detail::ValueInt   (std::move(rhs)); }
    inline detail::ValueFloat*  InternalMoveFloat (detail::ValueFloat&& rhs)  { type = kValueFloat;  return new (data) detail::ValueFloat (std::move(rhs)); }
    inline detail::ValueBool*   InternalMoveBool  (detail::ValueBool&& rhs)   { type = kValueBool;   return new (data) detail::ValueBool  (std::move(rhs)); }
    inline detail::ValueArray*  InternalMoveArray (detail::ValueArray&& rhs)  { type = kValueArray;  return new (data) detail::ValueArray (std::move(rhs)); }
    inline detail::ValueObject* InternalMoveObject(detail::ValueObject&& rhs) { type = kValueObject; return new (data) detail::ValueObject(std::move(rhs)); }

    inline detail::ValueString*       InternalGetString()       { jsonInternalAssert(type == kValueString); return reinterpret_cast<detail::ValueString*>      (data); }
    inline detail::ValueString const* InternalGetString() const { jsonInternalAssert(type == kValueString); return reinterpret_cast<detail::ValueString const*>(data); }
    inline detail::ValueInt*          InternalGetInt()          { jsonInternalAssert(type == kValueInt);    return reinterpret_cast<detail::ValueInt*>         (data); }
    inline detail::ValueInt const*    InternalGetInt()    const { jsonInternalAssert(type == kValueInt);    return reinterpret_cast<detail::ValueInt const*>   (data); }
    inline detail::ValueFloat*        InternalGetFloat()        { jsonInternalAssert(type == kValueFloat);  return reinterpret_cast<detail::ValueFloat*>       (data); }
    inline detail::ValueFloat const*  InternalGetFloat()  const { jsonInternalAssert(type == kValueFloat);  return reinterpret_cast<detail::ValueFloat const*> (data); }
    inline detail::ValueBool*         InternalGetBool()         { jsonInternalAssert(type == kValueBool);   return reinterpret_cast<detail::ValueBool*>        (data); }
    inline detail::ValueBool const*   InternalGetBool()   const { jsonInternalAssert(type == kValueBool);   return reinterpret_cast<detail::ValueBool const*>  (data); }
    inline detail::ValueArray*        InternalGetArray()        { jsonInternalAssert(type == kValueArray);  return reinterpret_cast<detail::ValueArray*>       (data); }
    inline detail::ValueArray const*  InternalGetArray()  const { jsonInternalAssert(type == kValueArray);  return reinterpret_cast<detail::ValueArray const*> (data); }
    inline detail::ValueObject*       InternalGetObject()       { jsonInternalAssert(type == kValueObject); return reinterpret_cast<detail::ValueObject*>      (data); }
    inline detail::ValueObject const* InternalGetObject() const { jsonInternalAssert(type == kValueObject); return reinterpret_cast<detail::ValueObject const*>(data); }

    template<typename T>
    void DestructValue(void* value)
    {
      T* t = reinterpret_cast<T*>(value);
      t->~T();

      detail::unused_arg(t);
    }

    inline void DestructValue(ValueType t, void* d)
    {
      switch(t)
      {
      case kValueString: DestructValue<detail::ValueString>(d); break;
      case kValueInt:    DestructValue<detail::ValueInt>   (d); break;
      case kValueFloat:  DestructValue<detail::ValueFloat> (d); break;
      case kValueBool:   DestructValue<detail::ValueBool>  (d); break;
      case kValueArray:  DestructValue<detail::ValueArray> (d); break;
      case kValueObject: DestructValue<detail::ValueObject>(d); break;
      case kValueNull: break;//no deleter necessary, nothing constructed into data

      default:
        jsonInternalAssert("Invalid type!" == std::string());
        break;
      }
    }

    template<typename StringT> Value const* GetMemberValue( StringT&& member ) const;
    template<typename StringT> Value*       GetMemberValue( StringT&& member );

    template<typename StringT>
    Value& GetOrAddMember( StringT&& memberName );
    
    template<typename StringT, typename ValueT>
    Value& GetOrAddMember( StringT&& memberName, ValueT&& value );
  };


  struct Member
  {
    std::string name;
    Value value;

    Member()
    {
    }

    Member( Member const& rhs )
      :name(rhs.name)
      ,value(rhs.value)
    {
    }

    Member( Member&& rhs )
      :name(std::move(rhs.name))
      ,value(std::move(rhs.value))
    {
    }

    Member& operator=( Member const& rhs )
    {
      name = rhs.name;
      value = rhs.value;
      return *this;
    }

    Member& operator=( Member&& rhs )
    {
      name = std::move(rhs.name);
      value = std::move(rhs.value);
      return *this;
    }

    template<typename StringT, typename ValueT>
    Member( StringT&& n, ValueT&& v )
      :name(std::forward<StringT>(n))
      ,value(std::forward<ValueT>(v))
    {
    }
  };


  template<typename StringT>
  bool Value::HasMember( StringT&& memberName ) const
  {
    detail::ValueObject const* obj = InternalGetObject();

    for( std::vector<json::Member>::const_iterator m = obj->members.begin(); m != obj->members.end(); ++m )
    {
      if( m->name == memberName ) return true;
    }
    return false;
  }

  template<typename StringT>
  inline Value const* Value::GetMemberValue( StringT&& memberName ) const
  {
    detail::ValueObject const* obj = InternalGetObject();

    for( std::vector<json::Member>::const_iterator m = obj->members.begin(); m != obj->members.end(); ++m )
    {
      if( m->name == memberName ) return &m->value;
    }

    detail::RaiseException("object does not contain member '" + std::string(memberName) + "'");
    return 0;
  }

  template<typename StringT>
  inline Value* Value::GetMemberValue( StringT&& memberName )
  {
    Value const* value = static_cast<Value const&>(*this).GetMemberValue(memberName);
    return const_cast<Value*>(value);
  }

  template<typename StringT>
  Value& Value::GetOrAddMember( StringT&& memberName )
  {
    return GetOrAddMember(std::forward<StringT>(memberName), Value());
  }

  template<typename StringT, typename ValueT>
  Value& Value::GetOrAddMember( StringT&& memberName, ValueT&& value )
  {
    detail::ValueObject* obj = InternalGetObject();

    for( std::vector<json::Member>::iterator m = obj->members.begin(); m != obj->members.end(); ++m )
    {
      if( m->name == memberName ) return m->value;
    }

    obj->members.push_back( Member(std::forward<StringT>(memberName), std::forward<ValueT>(value)));
    return obj->members.back().value;
  }


}

#endif
