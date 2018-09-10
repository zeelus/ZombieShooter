//
//  ZombieShooter.cpp
//  ZombieShooter
//
//  Created by Gilbert Gwizdała on 16.06.2018.
//

#include "ZombieShooter.hpp"
#include "ZombieMover.hpp"
#include "CharacterAnimationController.hpp"
#include "LiveComponent.hpp"

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Engine/EngineDefs.h>
#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/Animation.h>
#include <Urho3D/Graphics/AnimationState.h>
#include <Urho3D/Graphics/AnimationController.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Graphics/Terrain.h>
#include <Urho3D/Graphics/Skybox.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/Audio/Sound.h>
#include <Urho3D/Audio/SoundSource3D.h>
#include <Urho3D/Audio/SoundListener.h>
#include <Urho3D/Audio/Audio.h>

ZombieShooter::ZombieShooter(Context* context) : Application(context), drawDebug_(false)
{
    ZombieMover::RegisterObject(context);
    Character::RegisterObject(context);
    LiveComponent::RegisterObject(context);
    
}

void ZombieShooter::Setup() {
    engineParameters_[EP_LOG_NAME]          = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
    engineParameters_[EP_FULL_SCREEN]       = false;
    engineParameters_["WindowWidth"]        = 1280;
    engineParameters_["WindowHeight"]       = 720;
    engineParameters_["WindowResizable"]    = true;
    engineParameters_[EP_HEADLESS]          = false;
    engineParameters_[EP_SOUND]             = true;
    engineParameters_[EP_VSYNC]             = true;
}

void ZombieShooter::Start()
{
    Application::Start();
    
    Setup();
    
    CreateScene();
    
    CreateCharacter();
    
    SetupViewport();
    
    SubscribeToEvents();
    
    MouseMode(MM_ABSOLUTE);
}

const unsigned NUM_MODELS = 30;
const float MODEL_MOVE_SPEED = 1.0f;
const float MODEL_ROTATE_SPEED = 100.0f;

void ZombieShooter::CreateScene()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    scene_ = new Scene(context_);
    
    scene_->CreateComponent<Octree>();
    scene_->CreateComponent<DebugRenderer>();
    
    Node* zoneNode = scene_->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetAmbientColor(Color(0.5f, 0.5f, 0.5f));
    zone->SetFogColor(Color(0.4f, 0.5f, 0.8f));
    zone->SetFogStart(100.0f);
    zone->SetFogEnd(300.0f);
    
    Node* skyNode=scene_->CreateChild("Sky");
    skyNode->SetScale(1000.0f);
    Skybox* skybox=skyNode->CreateComponent<Skybox>();
    skybox->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    skybox->SetMaterial(cache->GetResource<Material>("Materials/Skybox.xml"));
    
    Node* terrainNode=scene_->CreateChild("Terrain");
    terrainNode->SetPosition(Vector3(3.0f,-0.4f));
    Urho3D::Terrain *terrain = terrainNode->CreateComponent<Terrain>();
    terrain->SetPatchSize(128);
    terrain->SetSpacing(Vector3(2,0.5,2));
    terrain->SetSmoothing(true);
    terrain->SetHeightMap(cache->GetResource<Image>("Textures/HeightMap.png"));
    terrain->SetMaterial(cache->GetResource<Material>("Materials/Terrain.xml"));
    terrain->SetCastShadows(true);
    terrain->SetOccluder(true);
    
    auto* terrainBody = terrainNode->CreateComponent<RigidBody>();
    terrainBody->SetCollisionLayer(2);
    
    auto* terrainShape = terrainNode->CreateComponent<CollisionShape>();
    terrainShape->SetTerrain();

    
    Vector<Node*> zList;
    for (unsigned i = 0; i < NUM_MODELS; ++i)
    {
        auto z = CreateZombie(cache, i, terrain);
        zList.Push(z);
    }
    this->zombies = zList;
    
    cameraNode_ = scene_->CreateChild("Camera");
    Camera* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetFarClip(200.0f);
    cameraNode_->SetPosition(Vector3(0.0, 0.0, -5.0));
    
    auto adjGunNode = cameraNode_->CreateChild("Gun");
    adjGunNode->SetRotation(Quaternion(-90, Vector3(0, 1, 0)));
    adjGunNode->SetScale(0.001);
    adjGunNode->SetPosition(Vector3(-0.1, -0.05, 0.2));
    auto gunNode = adjGunNode->CreateComponent<AnimatedModel>();
    gunNode->SetModel(cache->GetResource<Model>("Models/ak_47/ak_47.mdl"));
    gunNode->SetMaterial(cache->GetResource<Material>("Models/ak_47/Materials/ak_47.xml"));
    
    
    Sound* sound = cache->GetResource<Sound>("Music/Ninja Gods.ogg");
    sound->SetLooped(true);
    Node* node = scene_->CreateChild("Sound");
    SoundSource* sound_source = node->CreateComponent<SoundSource>();
    //sound_source->Play(sound);
    
}

void ZombieShooter::CreateCharacter() {
    
    auto* cache = GetSubsystem<ResourceCache>();
    
    Node* objectNode = scene_->CreateChild("Character");
    objectNode->SetPosition(Vector3(0.0f, 1.0f, 0.0f));
    
    // spin node
    Node* adjustNode = objectNode->CreateChild("AdjNode");
    adjustNode->SetRotation( Quaternion(180, Vector3(0,1,0) ) );
    adjustNode->SetScale(0.01);
    
    // Create the rendering component + animation controller
    auto* object = adjustNode->CreateComponent<AnimatedModel>();
    object->SetModel(cache->GetResource<Model>("Models/Character/Character.mdl"));
    object->SetMaterial(cache->GetResource<Material>("Models/Character/Materials/_Body.xml"));
    object->SetCastShadows(true);
    adjustNode->CreateComponent<CharacterAnimationController>();
    
    object->GetSkeleton().GetBone("RightArm")->animated_ = false;
    object->GetSkeleton().GetBone("RightArm")->node_->SetScale(0.00001);
    object->GetSkeleton().GetBone("LeftArm")->animated_ = false;
    object->GetSkeleton().GetBone("LeftArm")->node_->SetScale(0.00001);

    
//    // Set the head bone for manual control
    
    object->GetSkeleton().GetBone("Head")->animated_ = false;
    
//    auto headNode = object->GetSkeleton().GetBone("Head")->node_;
//    auto adjGunNode = headNode->CreateChild();
//    adjGunNode->SetRotation(Quaternion(-90, Vector3(0, 1, 0)));
//    adjGunNode->SetScale(0.1);
//    adjGunNode->SetPosition(Vector3(0, 0, 30.0));
//    auto gunNode = adjGunNode->CreateComponent<AnimatedModel>();
//    gunNode->SetModel(cache->GetResource<Model>("Models/ak_47/ak_47.mdl"));
//    gunNode->SetMaterial(cache->GetResource<Material>("Models/ak_47/Materials/ak_47.xml"));
    
    // Create rigidbody, and set non-zero mass so that the body becomes dynamic
    auto* body = objectNode->CreateComponent<RigidBody>();
    body->SetCollisionLayer(1);
    body->SetMass(1.0f);
    
    // Set zero angular factor so that physics doesn't turn the character on its own.
    // Instead we will control the character yaw manually
    body->SetAngularFactor(Vector3::ZERO);
    
    // Set the rigidbody to signal collision also when in rest, so that we get ground collisions properly
    body->SetCollisionEventMode(COLLISION_ALWAYS);
    
    // Set a capsule shape for collision
    auto* shape = objectNode->CreateComponent<CollisionShape>();
    shape->SetCapsule(0.7f, 1.8f, Vector3(0.0f, 0.9f, 0.0f));
    
    character_ = objectNode->CreateComponent<Character>();

    objectNode->CreateComponent<LiveComponent>();
    
    for(auto zNode : this->zombies) {
        ZombieMover* zMover = zNode->GetComponent<ZombieMover>();
        zMover->SetCharacter(character_);
    }
    
}

Node* ZombieShooter::CreateZombie(Urho3D::ResourceCache *cache, unsigned int i, Urho3D::Terrain *terrain) {
    Node* modelNode = scene_->CreateChild("Zombie " + String(i));
    float x = Random(40.0f) - 20.0f;
    float z = Random(40.0f) - 20.0f;
    float y = terrain->GetHeight(Vector3(x, 0, z)) + 0.1f;
    modelNode->SetPosition(Vector3(x, y, z));
    modelNode->SetRotation(Quaternion(0.0f, Random(360.0f), 0.0f));
    modelNode->SetScale(0.01);
    
    Node* adjustNode = modelNode->CreateChild("AdjNode");
    Quaternion qAdjRot(180, Vector3(0,1,0) ); // rotate it by 180
    adjustNode->SetRotation( qAdjRot );
    
    AnimatedModel* modelObject = adjustNode->CreateComponent<AnimatedModel>();
    modelObject->SetModel(cache->GetResource<Model>("Models/Zombie/Zombie.mdl"));
    modelObject->SetMaterial(cache->GetResource<Material>("Models/Zombie/Materials/Material.xml"));
    modelObject->SetCastShadows(true);
    adjustNode->CreateComponent<AnimationController>();
    
    auto* body = modelNode->CreateComponent<RigidBody>();
    body->SetCollisionLayer(1);
    body->SetMass(1.0f);
    body->SetAngularFactor(Vector3::ZERO);
    body->SetCollisionEventMode(COLLISION_ALWAYS);
    body->SetFriction(100.0f);
    
    auto* shape = modelNode->CreateComponent<CollisionShape>();
    shape->SetCapsule(80.0f, 160.0f, Vector3(0.0f, 80.0f, 0.0f));
    
    ZombieMover* mover = modelNode->CreateComponent<ZombieMover>();
    mover->SetParameters(MODEL_MOVE_SPEED, MODEL_ROTATE_SPEED);
    
    return modelNode;
}

void ZombieShooter::SetupViewport()
{
    Renderer* renderer = GetSubsystem<Renderer>();
    
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);
}

void ZombieShooter::SubscribeToEvents()
{
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(ZombieShooter, HandleUpdate));
    SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(ZombieShooter, HandlePostRenderUpdate));
}

void ZombieShooter::HandleUpdate(StringHash eventType, VariantMap& eventData) {

    auto* input = this->GetSubsystem<Input>();
    
    if (character_) {
        
        character_->controls_.Set(CTRL_FORWARD | CTRL_BACK | CTRL_LEFT | CTRL_RIGHT | CTRL_JUMP, false);
        
        character_->controls_.Set(CTRL_FORWARD, input->GetKeyDown(KEY_W));
        character_->controls_.Set(CTRL_BACK, input->GetKeyDown(KEY_S));
        character_->controls_.Set(CTRL_LEFT, input->GetKeyDown(KEY_A));
        character_->controls_.Set(CTRL_RIGHT, input->GetKeyDown(KEY_D));
        character_->controls_.Set(CTRL_JUMP, input->GetKeyDown(KEY_SPACE));
        
        
        character_->controls_.yaw_ += (float)input->GetMouseMoveX() * YAW_SENSITIVITY;
        character_->controls_.pitch_ += (float)input->GetMouseMoveY() * YAW_SENSITIVITY;
        character_->controls_.pitch_ = Clamp(character_->controls_.pitch_, -80.0f, 80.0f);
        character_->GetNode()->SetRotation(Quaternion(character_->controls_.yaw_, Vector3::UP));
    }
    
    Node* characterNode = character_->GetNode();
    
    // Get camera lookat dir from character yaw + pitch
    const Quaternion& rot = characterNode->GetRotation();
    Quaternion dir = rot * Quaternion(character_->controls_.pitch_, Vector3::RIGHT);
    
    // Turn head to camera pitch, but limit to avoid unnatural animation
    Node* headNode = characterNode->GetChild("Head", true);
    float limitPitch = Clamp(character_->controls_.pitch_, -45.0f, 45.0f);
    Quaternion spineDir = rot * Quaternion(limitPitch, Vector3(1.0f, 0.0f, 0.0f));
    // This could be expanded to look at an arbitrary target, now just look at a point in front
    Vector3 headWorldTarget = headNode->GetWorldPosition() + spineDir * Vector3(0.0f, 0.0f, 1.0f);
    headNode->LookAt(headWorldTarget, Vector3(0.0f, 1.0f, 0.0f));
    
    
    if (true)
    {
        Node* headNode = characterNode->GetChild("Head", true);
        cameraNode_->SetPosition(headNode->GetWorldPosition() + rot * Vector3(0.0f, 0.15f, 0.2f));
        cameraNode_->SetRotation(dir);
    }
    else
    {
        // Third person camera: position behind the character
        Vector3 aimPoint = characterNode->GetPosition() + rot * Vector3(0.0f, 1.7f, 0.0f);
        
        // Collide camera ray with static physics objects (layer bitmask 2) to ensure we see the character properly
        Vector3 rayDir = dir * Vector3::BACK;
        float rayDistance = CAMERA_INITIAL_DIST;
        PhysicsRaycastResult result;
        scene_->GetComponent<PhysicsWorld>()->RaycastSingle(result, Ray(aimPoint, rayDir), rayDistance, 2);
        if (result.body_)
            rayDistance = Min(rayDistance, result.distance_);
        rayDistance = Clamp(rayDistance, CAMERA_MIN_DIST, CAMERA_MAX_DIST);
        
        cameraNode_->SetPosition(aimPoint + rayDir * rayDistance);
        cameraNode_->SetRotation(dir);
    }
    
}

void ZombieShooter::HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData) {
    //scene_->GetComponent<PhysicsWorld>()->DrawDebugGeometry(true);
}
