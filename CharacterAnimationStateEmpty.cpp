//
//  CharacterAnimationStateEmpty.cpp
//  ZombieShooter
//
//  Created by pi29056 on 06.08.2018.
//

#include "CharacterAnimationStateEmpty.hpp"
using namespace Urho3D;

const String CharacterAnimationStateEmpty::getRunLocation() {
    return "Models/Character/run.ani";
}


const Urho3D::String CharacterAnimationStateEmpty::getWalkLeftLocation() { 
    return "Models/Character/leftWalk.ani";
}

const Urho3D::String CharacterAnimationStateEmpty::getWalkRightLocation() { 
    return "Models/Character/rightWalk.ani";
}

const Urho3D::String CharacterAnimationStateEmpty::getWalkBackLocation() { 
    return "Models/Character/walkBack.ani";
}

const Urho3D::String CharacterAnimationStateEmpty::getJumpLocation() { 
    return "Models/Character/jump.ani";
}

const Urho3D::String CharacterAnimationStateEmpty::getIdleLocation() { 
    return "Models/Character/idle.ani";
}


const Urho3D::String CharacterAnimationStateEmpty::getWalkLocation() { 
    return "Models/Character/run.ani";
}
