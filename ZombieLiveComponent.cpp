//
//  ZombieLiveComponent.cpp
//  ZombieShooter
//
//  Created by pi29056 on 15.09.2018.
//

#include "ZombieLiveComponent.hpp"
#include <Urho3D/Scene/Node.h>

using namespace Urho3D;

ZombieLiveComponent::ZombieLiveComponent(Context* context): LogicComponent(context), hitValue(0.2) {
    
}

void ZombieLiveComponent::RegisterObject(Context *context) {
    context->RegisterFactory<ZombieLiveComponent>();
}

void ZombieLiveComponent::getHit() {
    live -= hitValue;
    
    if(live <= 0) {
        this->zombieDie();
    }
    
}

void ZombieLiveComponent::zombieDie() {
    auto* zombieNode = this->node_;
    
    zombieNode->Remove();
}
