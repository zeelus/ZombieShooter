//
//  GunComponent.hpp
//  ZombieShooter
//
//  Created by pi29056 on 12.09.2018.
//

#ifndef GunComponent_hpp
#define GunComponent_hpp

#include <Urho3D/Core/Context.h>
#include <Urho3D/Input/Controls.h>
#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;

static float GUN_TIME_BETWEEN_SHOOTS = 0.2f;

class GunComponent: public LogicComponent {
    
    URHO3D_OBJECT(GunComponent, LogicComponent);
    
    void tryShoot(float timeStep);
    
    float maxDistance = 100.0;
    
    float lastTimeShoot = 0.0;
    float currentTime = 0.0;
    
public:
    
    GunComponent(Context* context);
    
    Node* cameraNode_;
    
    void FixedUpdate(float timeStep) override;
    
    static void RegisterObject(Context* context);
    
    Controls controls_;
    
};


#endif /* GunComponent_hpp */
