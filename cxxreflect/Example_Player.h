//
//  Example_Player.h
//  cxxreflect
//
//  Created by Nikita Ivanov on 3/11/20.
//  Copyright © 2020 Plak Corp. All rights reserved.
//

#ifndef Example_Player_h
#define Example_Player_h
#include <vector>
#include <cstdint>
#include <ctime>
#include "CXFramework/Object.h"
#include "CXFramework/Properties.h"

cxclass(Player)
{
public:
    // Fields
    float mX, mY, mZ, mSpeed;
    
    uint32_t mModelHash;
    bool mWasSpawned;
    time_t mSpawnTime;
    
    std::vector<int> mActivatedTriggers;
    std::vector<float> mTriggerCoefficients;
    
    std::string mUsername;
    std::string mNickname;
    
    // Define properties for serialization
    properties(Player) (
        property(mX, "PositionX"),
        property(mY, "PositionY"),
        property(mZ, "PositionZ"),
        property(mSpeed, "SpeedKPH"),
        
        property(mModelHash, "ModelHash"),
        property(mWasSpawned, "WasSpawned"),
        property(mSpawnTime, "SpawnTime"),
        
        property(mActivatedTriggers, "ActiveTriggers"),
        property(mTriggerCoefficients, "TriggerCoeffs"),
        
        property(mUsername, "Username"),
        property(mNickname, "Nickname")
    );
};

#endif /* Example_Player_h */
