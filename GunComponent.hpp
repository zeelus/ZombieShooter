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

class GunComponent: public LogicComponent {
    
    URHO3D_OBJECT(GunComponent, LogicComponent);
    
public:
    
    GunComponent(Context* context);
    
    void FixedUpdate(float timeStep) override;
    
    static void RegisterObject(Context* context);
    
    Controls controls_;
    
};


#endif /* GunComponent_hpp */
