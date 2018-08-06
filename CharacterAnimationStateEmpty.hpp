//
//  CharacterAnimationStateEmpty.hpp
//  ZombieShooter
//
//  Created by pi29056 on 06.08.2018.
//

#ifndef CharacterAnimationStateEmpty_hpp
#define CharacterAnimationStateEmpty_hpp

#include <stdio.h>
#include <Urho3D/Container/Str.h>

using namespace Urho3D;

class CharacterAnimationStateEmpty {
    
public:
    const String getWalkLocation();
    const String getRunLocation();
    const String getWalkLeftLocation();
    const String getWalkRightLocation();
    const String getWalkBackLocation();
    const String getJumpLocation();
    const String getIdleLocation();
    
};

#endif /* CharacterAnimationStateEmpty_hpp */
