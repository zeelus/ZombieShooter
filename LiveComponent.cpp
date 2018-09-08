//
//  LiveComponent.cpp
//  ZombieShooter
//
//  Created by pi29056 on 08.09.2018.
//

#include "LiveComponent.hpp"
#include <Urho3D/Core/Context.h>
#include <stdio.h>

LiveComponent::LiveComponent(Context* context): LogicComponent(context){
    live = 1.0;
}

double LiveComponent::getLive() {
    return this->live;
}

void LiveComponent::setLive(double live) {
    this->live = live;
    
    if(live < 0) {
        printf("Game over");
    }
}

void LiveComponent::RegisterObject(Context* context) {
    context->RegisterFactory<LiveComponent>();
}
