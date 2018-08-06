//
//  CharacterAnimationController.hpp
//  ZombieShooter
//
//  Created by pi29056 on 05.08.2018.
//

#include <Urho3D/Graphics/AnimationController.h>
#include "CharacterAnimationStateEmpty.hpp"

#ifndef CharacterAnimationController_hpp
#define CharacterAnimationController_hpp

#include <stdio.h>

using namespace Urho3D;

class CharacterAnimationController: public AnimationController {
private:
    
    CharacterAnimationStateEmpty emptyState;
    
    bool isEmptyState;
    
    
    
public:
    
    static void RegisterObject(Context* context);
    
    void setIsEmpty(bool isEmpty);
    
    void PlayRun();
    void PlayWalk();
    void PlayWalkLeft();
    void PlayWalkRight();
    void PlayWalkBack();
    void PlayJump();
    void PlayIdle();
    
};

#endif /* CharacterAnimationController_hpp */
