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
    ///Setup
    void Setup();
    /// Construct the scene content.
    void CreateScene();
    /// Construct an instruction text to the UI.
    void CreateInstructions();
    /// Set up a viewport for displaying the scene.
    void SetupViewport();
    /// Subscribe to application-wide logic update and post-render update events.
    void SubscribeToEvents();
    /// Read input and moves the camera.
    void MoveCamera(float timeStep);
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle the post-render update event.
    void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);
    
    /// Flag for drawing debug geometry.
    bool drawDebug_;
};

#endif /* ZombieShooter_hpp */
