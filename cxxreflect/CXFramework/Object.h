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

namespace CX
{
    class Object
    {
    public:
        typedef String Type;
        
        virtual ~Object() {}
        virtual Type GetType() const = 0;
        virtual String ToString() const = 0;
        virtual bool Equals(const Object&) const = 0;
    };
}


// Macros to create CX-capable classes
#define STRINGIFY(x) #x

#define cxclass(T) \
namespace CX { \
class __BasicObject_##T : public CX::Object { \
public: \
CX::Object::Type GetType() const { return STRINGIFY(T); } \
CX::String ToString() const { return STRINGIFY(T); } \
bool Equals(const CX::Object& obj) const { return this->GetType() == obj.GetType(); } \
}; \
}\
class T : public CX::__BasicObject_##T, public CX::Stats::Tracker<T>
#define extends(...) , __VA_ARGS__
#define implements extends

#endif /* Object_h */
