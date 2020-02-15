// Scene.h
// An abstraction of what appears on screen

#ifndef SCENE_H
#define SCENE_H

#include "Engine.h"

namespace App {

  // Base class for all scenes
  class Scene {

    public:

      // Constructor
      Scene(Engine& e) : engine(e) {}

      // Virtual destructor
      virtual ~Scene() {}

      // When the engine begins to use this scene
      virtual void switchTo() {}

      // When this engine stops using this scene
      virtual void switchFrom() {}

      // Handle keyboard input
      virtual void handleKeyboardInput(
          int key, int scancode, int action, int mods) {}

      // Send mouse button inputs to application
      virtual void handleMouseButtonInput(
          int button, int action, int mods) {}

      // Send mouse scroll inputs to application
      virtual void handleMouseScrollInput(
          double xoffset, double yoffset) {}

      // Update application logic
      virtual void update(double dt) {}

      // Allow the scene to handle imgui
      virtual void handleImgui() {}

      // Render entities on screen
      virtual void render() {}

    protected:

      // Provide scenes with engine utilities
      Engine& engine;
  };
}

#endif
