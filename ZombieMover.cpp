//
//  Mover.cpp
//  ZombieShooter
//
//  Created by Gilbert Gwizdała on 18.06.2018.
//

#include "ZombieMover.hpp"
#include "LiveComponent.hpp"

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
    SubscribeToEvent(GetNode(), E_NODECOLLISION, URHO3D_HANDLER(ZombieMover, HandleNodeCollision));
}

void ZombieMover::Update(float timeStep) {
    
    if(characterPtr) {
        auto characterNode = characterPtr->GetNode();
        Vector3 charcterZVector =  this->GetNode()->GetPosition() - characterNode->GetPosition();
        float len = charcterZVector.Length();
        
        
        if( len > 5.0) {
            node_->Translate(Vector3::FORWARD * moveSpeed_ * timeStep);
        } else {
            node_->Translate(charcterZVector.Normalized() * moveSpeed_ * timeStep);
            node_->LookAt(characterNode->GetPosition());
        }
        
        node_->Translate(Vector3::FORWARD * moveSpeed_ * timeStep);

        auto* animCtrl = node_->GetComponent<AnimationController>(true);
        animCtrl->Play("Models/Zombie/ZombieWalk.ani", 0, true, 0.2f);
    }

}

void ZombieMover::SetCharacter(Character* ptr) {
    this->characterPtr = ptr;
}

void ZombieMover::HandleNodeCollision(StringHash eventType, VariantMap& eventData) {
    
    using namespace NodeCollision;
    
    Node* node = (Node*) eventData[P_OTHERNODE].GetPtr();
    Character* character = node->GetComponent<Character>();
    
    if(character) {
        auto live = node->GetComponent<LiveComponent>();
        live->setLive(live->getLive() - 0.1);
    }
}

