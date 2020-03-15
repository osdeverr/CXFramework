//
//  Interface.cpp
//  cxxreflect
//
//  Created by Nikita Ivanov on 3/14/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#include <iostream>
#include "Interface.h"
#include "Object.h"

CX::Interface::Interface(const CX::HInterface h)
{
    Object* pObject = dynamic_cast<Object*>(this);
    std::cout << pObject->ToString() << " interfaced" << std::endl;
}
