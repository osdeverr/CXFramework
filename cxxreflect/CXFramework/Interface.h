//
//  Interface.h
//  cxxreflect
//
//  Created by Nikita Ivanov on 3/14/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef Interface_h
#define Interface_h

namespace CX
{
    typedef void(*HInterface)();
    class Interface
    {
    public:
        virtual ~Interface() {}
        Interface(const HInterface h);
        
        template<class T>
        T* As()
        {
            return dynamic_cast<T>(this);
        }
    };
}

#define interface(T) \
namespace CX { \
class __BasicInterface_##T : public CX::Interface { \
public: \
static void Handle() {}; \
__BasicInterface_##T() : CX::Interface(__BasicInterface_##T::Handle) {} \
}; \
}\
class T : public CX::__BasicInterface_##T

#endif /* Interface_h */
