//
//  ZombieLiveComponent.hpp
//  ZombieShooter
//
//  Created by pi29056 on 15.09.2018.
//

#ifndef ZombieLiveComponent_hpp
#define ZombieLiveComponent_hpp

#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;

class ZombieLiveComponent: public LogicComponent {
    
    URHO3D_OBJECT(ZombieLiveComponent, LogicComponent);
    
    float live = 1.0;
    
    float hitValue;
    
    void zombieDie();
    
public:
    
    ZombieLiveComponent(Context* context);
    
    static void RegisterObject(Context* context);
    
    void getHit();
};

#endif /* ZombieLiveComponent_hpp */
