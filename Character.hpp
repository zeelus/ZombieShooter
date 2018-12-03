//
//  Character.hpp
//  ZombieShooter
//
//  Created by Gilbert Gwizdała on 18.07.2018.
//

#ifndef Character_hpp
#define Character_hpp

#include <stdio.h>

#include <Urho3D/Input/Controls.h>
#include <Urho3D/Scene/LogicComponent.h>
#include "CharacterAnimationController.hpp"
#include <Urho3D/Physics/RigidBody.h>

using namespace Urho3D;


const float MOVE_FORCE = 1.0f;
const float INAIR_MOVE_FORCE = 0.02f;
const float BRAKE_FORCE = 0.2f;
const float JUMP_FORCE = 4.5f;
const float YAW_SENSITIVITY = 0.1f;
const float INAIR_THRESHOLD_TIME = 0.1f;

/// Character component, responsible for physical movement according to controls, as well as animation.
class Character : public LogicComponent
{
    URHO3D_OBJECT(Character, LogicComponent);
    
public:
    /// Construct.
    explicit Character(Context* context);
    
    /// Register object factory and attributes.
    static void RegisterObject(Context* context);
    
    /// Handle startup. Called by LogicComponent base class.
    void Start() override;
    /// Handle physics world update. Called by LogicComponent base class.
    void FixedUpdate(float timeStep) override;
    
    /// Movement controls. Assigned by the main program each frame.
    Controls controls_;
    
private:
    /// Handle physics collision event.
    void HandleNodeCollision(StringHash eventType, VariantMap& eventData);
    
    /// Grounded flag for movement.
    bool onGround_;
    /// Jump flag.
    bool okToJump_;
    /// In air timer. Due to possible physics inaccuracy, character can be off ground for max. 1/10 second and still be allowed to move.
    float inAirTimer_;
    
    RigidBody* body;
    CharacterAnimationController* animCtrl;
};


#endif /* Character_hpp */
