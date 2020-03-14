//
//  main.cpp
//  cxxreflect
//
//  Created by Nikita Ivanov on 3/11/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Example_Player.h"
using json = nlohmann::json;

cxclass(TestClass)
{
public:
    CX::String ToString()
    {
        return "TestClass ToString override";
    }
};

cxclass(Point)
{
private:
    float mX, mY;
public:
    Point(float x, float y) : mX(x), mY(y) {}
    CX::String ToString()
    {
        return "Point @ " + std::to_string(mX) + ":" + std::to_string(mY);
    }
};

int main(int argc, const char * argv[]) {
    /*
    Point p(100, 200);
    std::cout << p.ToString() << std::endl;
    for(int i = 0; i < 50; i++)
        new Point(100, 100);
    std::cout <<
        "Stat info: " <<
        Point::CXMemoryUsage() <<
        " bytes used for " <<
        Point::CXNumActive() <<
        " active instances (" <<
        Point::CXNumCreated() <<
        " created overall)" <<
        std::endl;*/
    
    Player pl;
    pl.mX = 100.f;
    pl.mY = 666.f;
    pl.mZ = 228.f;
    pl.mSpeed = 1337.f;
    pl.mActivatedTriggers = {29, 91, 85, 832};
    pl.mTriggerCoefficients = {1.f, 0.4f, 0.8f, 5.f};
    pl.mSpawnTime = time(nullptr);
    pl.mModelHash = 0xDEADBEEF;
    pl.mUsername = "osdeverYT";
    pl.mNickname = "osdever";
    pl.mWasSpawned = true;
        
    CX::String jsonData = pl.CXToJSON();
    std::cout << jsonData << std::endl;

    return 0;
}
