//
//  GunComponent.cpp
//  ZombieShooter
//
//  Created by pi29056 on 12.09.2018.
//

#include "GunComponent.hpp"
#include "ZombieShooter.hpp"

#include <Urho3D/Audio/Sound.h>
#include <Urho3D/Audio/SoundSource3D.h>
#include <Urho3D/Audio/SoundListener.h>
#include <Urho3D/Audio/Audio.h>
#include <Urho3D/Resource/ResourceCache.h>

using namespace Urho3D;

void GunComponent::RegisterObject(Context* context)
{
    context->RegisterFactory<GunComponent>();
}

GunComponent::GunComponent(Context* context): Urho3D::LogicComponent(context) {
    
}

void GunComponent::FixedUpdate(float timeStep) {
    auto* soundSource = GetComponent<SoundSource>();
    
    if(controls_.IsDown(CTRL_LMOUSE)) {
        ResourceCache* cache = GetSubsystem<ResourceCache>();
        Sound* sound = cache->GetResource<Sound>("Music/AK47.ogg");
        sound->SetLooped(true);
        if(!soundSource->IsPlaying()) {
            soundSource->Play(sound);
        }

    }
    else {
        soundSource->Stop();
    }
}
