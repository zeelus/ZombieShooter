//
//  ZombieShooter.hpp
//  ZombieShooter
//
//  Created by Gilbert Gwizdała on 16.06.2018.
//

#ifndef ZombieShooter_hpp
#define ZombieShooter_hpp

#include <Urho3D/Engine/Application.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Graphics/Terrain.h>
#include "Character.hpp"

const float CAMERA_MIN_DIST = 1.0f;
const float CAMERA_INITIAL_DIST = 5.0f;
const float CAMERA_MAX_DIST = 20.0f;

namespace Urho3D
{
    
    class Node;
    class Scene;
    class String;
    
}

using namespace Urho3D;

class ZombieShooter : public Application
{
    URHO3D_OBJECT(ZombieShooter, Application);
    
public:
    /// Construct.
    ZombieShooter(Context* context);
    
    /// Setup after engine initialization and before running the main loop.
    virtual void Start();
    
    SharedPtr<Scene> scene_;
    SharedPtr<Node> cameraNode_;

    float yaw_;
    float pitch_;
    
protected:
    /// Return XML patch instructions for screen joystick layout for a specific sample app, if any.
    virtual String GetScreenJoystickPatchString() const { return
        "<patch>"
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />"
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Debug</replace>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">"
        "        <element type=\"Text\">"
        "            <attribute name=\"Name\" value=\"KeyBinding\" />"
        "            <attribute name=\"Text\" value=\"SPACE\" />"
        "        </element>"
        "    </add>"
        "</patch>";
    }
    

    
private:
    
    void Setup();
    
    void extracted(Urho3D::ResourceCache *cache, unsigned int i, Urho3D::Terrain *terrain);
    
    void CreateScene();
    
    void CreateCharacter();
    
    void SetupViewport();
    
    void SubscribeToEvents();
    
    void MoveCamera(float timeStep);
    
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    
    void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);
    
    void CreateZombie(Urho3D::ResourceCache *cache, unsigned int i, Urho3D::Terrain *terrain);
    
    /// Flag for drawing debug geometry.
    bool drawDebug_;

    WeakPtr<Character> character_;
};

#endif /* ZombieShooter_hpp */
