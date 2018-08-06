//
//  CharacterAnimationController.cpp
//  ZombieShooter
//
//  Created by pi29056 on 05.08.2018.
//

#include "CharacterAnimationController.hpp"
#include <Urho3D/Core/Context.h>

void CharacterAnimationController::PlayWalk() { 
    if(this->isEmptyState) {
        this->PlayExclusive(emptyState.getWalkLocation(), 0, 0.2f);
    } else {
        
    }
}

void CharacterAnimationController::PlayWalkLeft() {
    if(this->isEmptyState) {
        this->PlayExclusive(emptyState.getWalkLeftLocation(), 0, 0.2f);
    } else {
        
    }
}

void CharacterAnimationController::PlayWalkRight() { 
    if(this->isEmptyState) {
        this->PlayExclusive(emptyState.getWalkRightLocation(), 0, 0.2f);
    } else {
        
    }
}

void CharacterAnimationController::PlayWalkBack() { 
    if(this->isEmptyState) {
        this->PlayExclusive(emptyState.getWalkBackLocation(), 0, 0.2f);
    } else {
        
    }
}

void CharacterAnimationController::PlayJump() { 
    if(this->isEmptyState) {
        this->PlayExclusive(emptyState.getJumpLocation(), 0, 0.2f);
    } else {
        
    }
}

void CharacterAnimationController::PlayIdle() { 
    if(this->isEmptyState) {
        this->PlayExclusive(emptyState.getIdleLocation(), 0, 0.2f);
    } else {
        
    }
}

void CharacterAnimationController::PlayRun() { 
    if(this->isEmptyState) {
        this->PlayExclusive(emptyState.getRunLocation(), 0, 0.2f);
    } else {
        
    }
}

void CharacterAnimationController::setIsEmpty(bool isEmpty) {
    this->isEmptyState = isEmpty;
}
