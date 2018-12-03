//
//  LiveComponent.hpp
//  ZombieShooter
//
//  Created by Gilbert Gwizdała on 08.09.2018.
//

#ifndef LiveComponent_hpp
#define LiveComponent_hpp

#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Core/Context.h>

using namespace Urho3D;

class LiveComponent: public LogicComponent {
    
    URHO3D_OBJECT(LiveComponent, LogicComponent);
    
private:
    double live = 1.0;
    
public:
    
    LiveComponent(Context* context);
    
    static void RegisterObject(Context* context);
    
    void setLive(double live);
    double getLive();
};

#endif /* LiveComponent_hpp */
