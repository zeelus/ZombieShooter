//
//  Mover.cpp
//  ZombieShooter
//
//  Created by Gilbert Gwizdała on 18.06.2018.
//

#include "Mover.hpp"

#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/AnimationState.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Graphics/Terrain.h>

#include <Urho3D/DebugNew.h>

Mover::Mover(Context* context) :
LogicComponent(context),
moveSpeed_(0.0f),
rotationSpeed_(0.0f) {
    // Only the scene update event is needed: unsubscribe from the rest for optimization
    SetUpdateEventMask(USE_UPDATE);
}

void Mover::SetParameters(float moveSpeed, float rotationSpeed, const BoundingBox& bounds) {
    moveSpeed_ = moveSpeed;
    rotationSpeed_ = rotationSpeed;
    bounds_ = bounds;
}

void Mover::Update(float timeStep) {
    node_->Translate(Vector3::FORWARD * moveSpeed_ * timeStep);
    
    // If in risk of going outside the plane, rotate the model right
    Vector3 pos = node_->GetPosition();
    if (pos.x_ < bounds_.min_.x_ || pos.x_ > bounds_.max_.x_ || pos.z_ < bounds_.min_.z_ || pos.z_ > bounds_.max_.z_)
        node_->Yaw(rotationSpeed_ * timeStep);
    
    pos.y_ = this->terrain->GetHeight(pos);
    node_->SetPosition(pos);
    
    // Get the model's first (only) animation state and advance its time. Note the convenience accessor to other components
    // in the same scene node
    AnimatedModel* model = node_->GetComponent<AnimatedModel>(true);
    if (model->GetNumAnimationStates())
    {
        AnimationState* state = model->GetAnimationStates()[0];
        state->AddTime(timeStep);
    }
}

void Mover::SetTerrain(Urho3D::Terrain *terrain) {
    this->terrain = terrain;
}
