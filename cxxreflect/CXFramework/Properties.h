//
//  Properties.h
//  cxxreflect
//
//  Created by Nikita Ivanov on 3/14/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef Properties_h
#define Properties_h
#include "String.h"
#include "utils/json.hpp"

// Macros for convenience
#define CXXREFLECT_INTERNAL_PLISTNAME __CXProperties // Name of the class static field

/*
 --- 'properties' macro ---
 Declares a property block: can be used outside of a class declaration
 but should be kept in it for clarity
 Input:
 [ClassType] T - Class type
 Usage example:
 class ReflectedClass
 {
 public:
 // Class fields go here...
 
 // Define a property block for ReflectedClass
 properties(ReflectedClass) (
 // Properties go here...
 );
 };
 */
#define cxprops(T) \
typedef T __CXBaseClass; \
const std::string CXToJSON() const { \
return CX::Serialization::JSON::Serialize(*this); \
} \
static const __CXBaseClass CXFromJSON(const std::string& serialized) { \
return CX::Serialization::JSON::Deserialize<__CXBaseClass>(serialized); \
} \
constexpr static auto CXXREFLECT_INTERNAL_PLISTNAME = std::make_tuple

/*
 --- 'property' macro ---
 Declares a property: must be used in a property block
 
 Input:
 [ClassMember] member - Class/struct field to bind
 [Optional] [String] name - Name of the property: using the in-class
 field name if not specified
 Usage example:
 // Class fields
 std::string mStringMember;
 int mIntMember;
 bool mBoolMember;
 
 // Define a property block for ReflectedClass
 properties(ReflectedClass) (
 // Define a property automatically named 'mStringMember'
 property(mStringMember),
 // Define a property with a custom name
 property(mIntMember, "customPropertyName")
 );
 */
#define property(...) property_vararg(__VA_ARGS__, property_customname, property_autoname)(__VA_ARGS__)

// Internal macros for 'property'
#define property_autoname(member) CX::Reflection::Internal::DefineProperty(&__CXBaseClass::member, CXSTRINGIFY(member))
#define property_customname(member, name) CX::Reflection::Internal::DefineProperty(&__CXBaseClass::member, name)
#define property_vararg(_1,_2,NAME,...) NAME

/*
 --- 'enumerate' macro ---
 Uses a lambda to iterate through the properties of a class.
 Input:
 [TypeName] T - Class/struct typename; must have a defined property block
 [T] obj - T instance to be iterated
 Usage example:
 ReflectedClass cls;
 cls.mIntMember = 5;
 cls.mBoolMember = true;
 cls.mStringMember = "CXXRefl test";
 
 enumerate(ReflectedClass, cls) {
 std::cout << "Value " << name << " = " << value << std::endl;
 } cxxenum_end;
 */
#define cxenum(T, obj) \
constexpr auto nbProperties = std::tuple_size<decltype(T::CXXREFLECT_INTERNAL_PLISTNAME)>::value; \
CX::Reflection::Internal::ForIntSequence(std::make_index_sequence<nbProperties>{}, [&](auto i) { cxenum_init(T, obj);

// Internal macros for 'enumerate'
#define cxenum_init(T, obj) \
constexpr auto __property = std::get<i>(T::CXXREFLECT_INTERNAL_PLISTNAME); \
T& __object = obj; \
CX::String name = __property.name; \
auto& value = __object.*(__property.member); \
using type = typename decltype(__property)::Type
#define cxenum_end })

// Originally created for CXXReflect
namespace CX
{
    namespace Reflection
    {
        namespace Internal
        {
            template<class Class, typename MemberType>
            struct PropertyImpl
            {
                constexpr PropertyImpl(MemberType Class::*aMember, const char* aName) : member{aMember}, name{aName} {}
                MemberType Class::*member;
                const char* name;
                using Type = MemberType;
            };
        
            template <typename T, T... S, typename F>
            constexpr void ForIntSequence(std::integer_sequence<T, S...>, F&& f) {
                using unpack_t = int[];
                (void)unpack_t{(static_cast<void>((void) f(std::integral_constant<T, S>{})), 0)..., 0};
            }
        
            template<typename Class, typename T>
            constexpr auto DefineProperty(T Class::*member, const char* name) {
                return PropertyImpl<Class, T>{member, name};
            }
        }
    }

    namespace Serialization
    {
        namespace JSON
        {
            template<class T>
            const std::string Serialize(T& obj)
            {
                nlohmann::json j;
                cxenum(T, obj) {
                    j[name] = value;
                } cxenum_end;
                return j.dump(4);
            }
            
            template<class T>
            const T Deserialize(const std::string& s)
            {
                nlohmann::json j = nlohmann::json::parse(s);
                T obj;
                cxenum(T, obj)
                {
                    value = j.at(name).get<type>();
                } cxenum_end;
                return obj;
            }
        }
    }
}

#endif /* Properties_h */
