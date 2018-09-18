//
//  GunComponent.cpp
//  ZombieShooter
//
//  Created by pi29056 on 12.09.2018.
//

#include "GunComponent.hpp"
#include "ZombieShooter.hpp"
#include "ZombieLiveComponent.hpp"

#include <Urho3D/Audio/Sound.h>
#include <Urho3D/Audio/SoundSource3D.h>
#include <Urho3D/Audio/SoundListener.h>
#include <Urho3D/Audio/Audio.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Scene/Scene.h>

using namespace Urho3D;

void GunComponent::RegisterObject(Context* context)
{
    context->RegisterFactory<GunComponent>();
}

GunComponent::GunComponent(Context* context): Urho3D::LogicComponent(context) {
    
}

void GunComponent::FixedUpdate(float timeStep) {
    auto* soundSource = GetComponent<SoundSource>();
    
    currentTime += timeStep;
    
    if(controls_.IsDown(CTRL_LMOUSE)) {
        ResourceCache* cache = GetSubsystem<ResourceCache>();
        Sound* sound = cache->GetResource<Sound>("Music/AK47.ogg");
        sound->SetLooped(true);
        if(!soundSource->IsPlaying()) {
            soundSource->Play(sound);
        }
        
        this->tryShoot(timeStep);
    }
    else {
        soundSource->Stop();
    }
}

void GunComponent::tryShoot(float timeStep) {
    
    if((currentTime - lastTimeShoot) >= GUN_TIME_BETWEEN_SHOOTS) {
        lastTimeShoot = currentTime;
    } else {
        return;
    }
    
    PhysicsWorld* pw = GetScene()->GetComponent<PhysicsWorld>();
    
    Ray gunRay = Ray(cameraNode_->GetWorldPosition(), cameraNode_->GetWorldDirection());
    PhysicsRaycastResult result;

    pw->RaycastSingle(result, gunRay, maxDistance);
    
    if (result.body_) {
        
        Node* resultNode = result.body_->GetNode();
        if(auto* live = resultNode->GetComponent<ZombieLiveComponent>()){
            printf("%s get hit\n", resultNode->GetName().CString());
            live->getHit();
        }
        
    }
    
}
