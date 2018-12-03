//
//  ZombieLiveComponent.hpp
//  ZombieShooter
//
//  Created by Gilbert Gwizdała on 15.09.2018.
//

#ifndef ZombieLiveComponent_hpp
#define ZombieLiveComponent_hpp

#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/Constraint.h>

using namespace Urho3D;

class ZombieLiveComponent: public LogicComponent {
    
    URHO3D_OBJECT(ZombieLiveComponent, LogicComponent);
    
    float live = 1.0;
    
    float hitValue;
    
    void zombieDie();
    
    void CreateRagdollBone(const String& boneName, ShapeType type, const Vector3& size, const Vector3& position, const Quaternion& rotation);
    
    void CreateRagdollConstraint(const String& boneName, const String& parentName, ConstraintType type,
                            const Vector3& axis, const Vector3& parentAxis, const Vector2& highLimit, const Vector2& lowLimit,
                                 bool disableCollision = true);
    
public:
    
    ZombieLiveComponent(Context* context);
    
    static void RegisterObject(Context* context);
    
    void getHit();
};

#endif /* ZombieLiveComponent_hpp */
