//
//  Mover.hpp
//  ZombieShooter
//
//  Created by Gilbert Gwizdała on 18.06.2018.
//

#ifndef Mover_hpp
#define Mover_hpp

#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Math/Rect.h>
#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Math/BoundingBox.h>
#include <Urho3D/Graphics/Terrain.h>

#include "Character.hpp"


using namespace Urho3D;

static float INIT_ZOMBIE_MOVE_SPEED = 0.0f;
static float INIT_ZOMBIE_ROTATION_SPEED = 0.0f;
static float ZOMBIE_RADAR_RADIUS = 20.0f;
static float ZOMBIE_HIT_VALUE = 0.1f;

/// Custom logic component for moving the animated model and rotating at area edges.
class ZombieMover : public LogicComponent
{
    URHO3D_OBJECT(ZombieMover, LogicComponent);
    
public:
    /// Construct.
    ZombieMover(Context* context);
    
    static void RegisterObject(Context* context);
    
    void SetParameters(float moveSpeed, float rotateSpeed);
    virtual void Update(float timeStep);
    
    /// Return forward movement speed.
    float GetMoveSpeed() const { return moveSpeed_; }
    /// Return rotation speed.
    float GetRotationSpeed() const { return rotationSpeed_; }
    
    void Start() override;
    
    void SetCharacter(Character* ptr);
    
    void HandleNodeCollision(StringHash eventType, VariantMap& eventData);
    
    Character* characterPtr;
    
private:
    /// Forward movement speed.
    float moveSpeed_;
    /// Rotation speed.
    float rotationSpeed_;
    
    
    
};

#endif /* Mover_hpp */
