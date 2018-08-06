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



//
//    switch (state) {
//        case CharacterAnimationState::run:
//            return "Models/Character/run.ani";
//        case CharacterAnimationState::walkBack:
//            return "Models/Character/walkBack.ani";
//        case CharacterAnimationState::walkLeft:
//            return "";
//        case CharacterAnimationState::walkRight:
//            return "Models/Character/rightWalk.ani";
//        case CharacterAnimationState::walk:
//            return "Models/Character/run.ani";
//        case CharacterAnimationState::jump:
//            return "Models/Character/jump.ani";
//        case CharacterAnimationState::idle:
//            return "Models/Character/idle.ani";
//    }
//
//}
