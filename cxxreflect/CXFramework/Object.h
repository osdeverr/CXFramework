//
//  Object.h
//  cxxreflect
//
//  Created by Nikita Ivanov on 3/14/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef Object_h
#define Object_h
#include "Stats.h"
#include "String.h"
#include "Methods.h"
#include <vector>

namespace CX
{
    class Object
    {
    public:
        using Type = String;
        using Methods = std::vector<CX::Reflection::ClassMethod>;
        
        virtual ~Object() {}
        virtual Type GetType() const = 0;
        virtual String ToString() const = 0;
        virtual bool Equals(const Object&) const = 0;
    };
}


// Macros to create CX-capable classes

#define cxclass(T) \
namespace CX { \
class _BasicObject_##T : public CX::Object { \
public: \
operator CX::Object*() { return this; } \
CX::Object::Type GetType() const { return CXSTRINGIFY(T); } \
CX::String ToString() const { return CXSTRINGIFY(T); } \
bool Equals(const CX::Object& obj) const { return this->GetType() == obj.GetType(); } \
}; \
}\
class T : public CX::_BasicObject_##T, public CX::Stats::Tracker<T>
#define extends(...) , __VA_ARGS__
#define implements extends
#define cxobject CX::Object*

#endif /* Object_h */
