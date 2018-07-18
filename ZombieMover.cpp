//
//  Mover.cpp
//  ZombieShooter
//
//  Created by Gilbert Gwizdała on 18.06.2018.
//

#include "ZombieMover.hpp"

#include <Urho3D/Core/Context.h>
#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/AnimationState.h>
#include <Urho3D/Graphics/Terrain.h>
#include <Urho3D/Graphics/Terrain.h>
#include <Urho3D/Graphics/AnimationController.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>


#include <Urho3D/DebugNew.h>

ZombieMover::ZombieMover(Context* context) :
LogicComponent(context),
moveSpeed_(0.0f),
rotationSpeed_(0.0f) {
    // Only the scene update event is needed: unsubscribe from the rest for optimization
    SetUpdateEventMask(USE_UPDATE);
}

void ZombieMover::RegisterObject(Context *context) {
    context->RegisterFactory<ZombieMover>();
}

void ZombieMover::SetParameters(float moveSpeed, float rotationSpeed) {
    moveSpeed_ = moveSpeed;
    rotationSpeed_ = rotationSpeed;
}

void ZombieMover::Start() {
    
}

void ZombieMover::Update(float timeStep) {
    
    node_->Translate(Vector3::FORWARD * moveSpeed_ * timeStep);

    Vector3 pos = node_->GetPosition();

    auto* animCtrl = node_->GetComponent<AnimationController>(true);
    animCtrl->Play("Models/Zombie/ZombieWalk.ani", 0, true, 0.2f);

}



