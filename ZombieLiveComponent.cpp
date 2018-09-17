//
//  ZombieLiveComponent.cpp
//  ZombieShooter
//
//  Created by pi29056 on 15.09.2018.
//

#include "ZombieLiveComponent.hpp"
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Physics/Constraint.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Graphics/AnimatedModel.h>


#include "ZombieMover.hpp"

using namespace Urho3D;

ZombieLiveComponent::ZombieLiveComponent(Context* context): LogicComponent(context), hitValue(0.5) {
    
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
    
    zombieNode->GetComponent<ZombieMover>()->characterPtr = nullptr;
    auto* animation = zombieNode->GetComponent<AnimationController>(true);
    animation->StopAll();
    
    zombieNode->RemoveComponent<RigidBody>();
    zombieNode->RemoveComponent<CollisionShape>();
    
    CreateRagdollBone("Head", SHAPE_BOX, Vector3(20.0f, 20.0f, 20.0f), Vector3(0.0f, 1.0f, 0.0f), Quaternion(0.0f, 0.0f, 0.0f));
    CreateRagdollBone("Hips", SHAPE_BOX, Vector3(30.0f, 60.0f, 20.0f), Vector3(0.0f, 10.0f, 0.0f), Quaternion(0.0f, 0.0f, 0.0f));
    CreateRagdollBone("RightArm", SHAPE_CAPSULE, Vector3(15.0f, 40.0f, 20.0f), Vector3(-10.0f, 0.0f, 0.0f), Quaternion(0.0f, 0.0f, 90.0f));
    CreateRagdollBone("LeftArm", SHAPE_CAPSULE, Vector3(15.0f, 40.0f, 20.0f), Vector3(10.0f, 0.0f, 0.0f), Quaternion(0.0f, 0.0f, 90.0f));
    CreateRagdollBone("RightForeArm", SHAPE_CAPSULE, Vector3(15.0f, 40.0f, 20.0f), Vector3(-20.0f, 0.0f, 0.0f), Quaternion(0.0f, 0.0f, 90.0f));
    CreateRagdollBone("LeftForeArm", SHAPE_CAPSULE, Vector3(15.0f, 40.0f, 20.0f), Vector3(20.0f, 0.0f, 0.0f), Quaternion(0.0f, 0.0f, 90.0f));
    CreateRagdollBone("RightUpLeg", SHAPE_CAPSULE, Vector3(20.0f, 40.0f, 20.0f), Vector3(0.0f, -30.0f, 0.0f), Quaternion(0.0f, 0.0f, 0.0f));
    CreateRagdollBone("LeftUpLeg", SHAPE_CAPSULE, Vector3(20.0f, 40.0f, 20.0f), Vector3(0.0f, -30.0f, 0.0f), Quaternion(0.0f, 0.0f, 0.0f));
    CreateRagdollBone("LeftLeg", SHAPE_CAPSULE, Vector3(20.0f, 40.0f, 20.0f), Vector3(0.0f, -30.0f, 0.0f), Quaternion(0.0f, 0.0f, 0.0f));
    CreateRagdollBone("RightLeg", SHAPE_CAPSULE, Vector3(20.0f, 40.0f, 20.0f), Vector3(0.0f, -30.0f, 0.0f), Quaternion(0.0f, 0.0f, 0.0f));
    
    CreateRagdollConstraint("Head", "Hips", CONSTRAINT_CONETWIST, Vector3::LEFT, Vector3::LEFT, Vector2(0.0f, 30.0f), Vector2::ZERO);
    CreateRagdollConstraint("LeftArm", "Hips", CONSTRAINT_CONETWIST, Vector3::DOWN, Vector3::UP, Vector2(90.0f, 45.0f), Vector2::ZERO, false);
    CreateRagdollConstraint("RightArm", "Hips", CONSTRAINT_CONETWIST, Vector3::DOWN, Vector3::UP, Vector2(45.0f, 45.0f), Vector2::ZERO, false);
    CreateRagdollConstraint("LeftArm", "LeftForeArm", CONSTRAINT_HINGE, Vector3::BACK, Vector3::BACK, Vector2(90.0f, 0.0f), Vector2::ZERO);
    CreateRagdollConstraint("RightArm", "RightForeArm", CONSTRAINT_HINGE, Vector3::BACK, Vector3::BACK, Vector2(90.0f, 0.0f), Vector2::ZERO);
    CreateRagdollConstraint("LeftUpLeg", "Hips", CONSTRAINT_CONETWIST, Vector3::DOWN, Vector3::UP, Vector2(0.0f, 90.0f), Vector2::ZERO, false);
    CreateRagdollConstraint("RightUpLeg", "Hips", CONSTRAINT_CONETWIST, Vector3::DOWN, Vector3::UP, Vector2(0.0f, 90.0f), Vector2::ZERO, false);
    CreateRagdollConstraint("LeftLeg", "LeftUpLeg", CONSTRAINT_CONETWIST, Vector3::DOWN, Vector3::UP, Vector2(90.0f, 90.0f), Vector2::ZERO, false);
    CreateRagdollConstraint("RightLeg", "RightUpLeg", CONSTRAINT_CONETWIST, Vector3::DOWN, Vector3::UP, Vector2(90.0f, 90.0f), Vector2::ZERO, false);
    
    zombieNode->GetComponent<ZombieMover>()->Remove();
    this->Remove();
}

void ZombieLiveComponent::CreateRagdollBone(const String& boneName, ShapeType type, const Vector3& size, const Vector3& position,
                                      const Quaternion& rotation)
{

    Node* boneNode = node_->GetChild(boneName, true);
    if (!boneNode)
    {
        return;
    }
    
    auto* body = boneNode->CreateComponent<RigidBody>();
    // Set mass to make movable
    body->SetMass(1.0f);
    // Set damping parameters to smooth out the motion
    body->SetLinearDamping(0.05f);
    body->SetAngularDamping(0.85f);
    // Set rest thresholds to ensure the ragdoll rigid bodies come to rest to not consume CPU endlessly
    body->SetLinearRestThreshold(3.5f);
    body->SetAngularRestThreshold(4.5f);
    body->SetCollisionLayer(1);
    
    
    auto* shape = boneNode->CreateComponent<CollisionShape>();
    // We use either a box or a capsule shape for all of the bones
    if (type == SHAPE_BOX)
        shape->SetBox(size, position, rotation);
    else
        shape->SetCapsule(size.x_, size.y_, position, rotation);
}

void ZombieLiveComponent::CreateRagdollConstraint(const String& boneName, const String& parentName, ConstraintType type,
                                            const Vector3& axis, const Vector3& parentAxis, const Vector2& highLimit, const Vector2& lowLimit,
                                            bool disableCollision)
{
    Node* boneNode = node_->GetChild(boneName, true);
    Node* parentNode = node_->GetChild(parentName, true);
    if (!boneNode)
    {
        return;
    }
    if (!parentNode)
    {
        return;
    }
    
    auto* constraint = boneNode->CreateComponent<Constraint>();
    constraint->SetConstraintType(type);
    // Most of the constraints in the ragdoll will work better when the connected bodies don't collide against each other
    constraint->SetDisableCollision(disableCollision);
    // The connected body must be specified before setting the world position
    constraint->SetOtherBody(parentNode->GetComponent<RigidBody>());
    // Position the constraint at the child bone we are connecting
    constraint->SetWorldPosition(boneNode->GetWorldPosition());
    // Configure axes and limits
    constraint->SetAxis(axis);
    constraint->SetOtherAxis(parentAxis);
    constraint->SetHighLimit(highLimit);
    constraint->SetLowLimit(lowLimit);
}
