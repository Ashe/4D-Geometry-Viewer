// Viewer.h
// A scene used to view geometry

#ifndef EDITOR_H
#define EDITOR_H

#include <memory>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/matrix.hpp>

#include "Scene.h"
#include "Camera.h"
#include "Camera4D.h"

#include "shaders/Vertex.h"
#include "shaders/Fragment.h"

#include "polytopes/Hypercube.h"

namespace App {

  // A scene with the ability to view geomery
  class Viewer : public Scene {

    public:

      // Constructor
      Viewer(Engine& e);

      // Alter the speed of the camera
      void handleMouseScrollInput(double x, double y) override;

      // Handle keyboard input for keybindings
      void handleKeyboardInput(
          int key, int scan, int action, int mods) override;

      // Update the viewer
      void update(double dt) override;

      // Render geometry
      void render() override;

      // Grant the viewer access to imgui
      void handleImgui() override;

    private:

      // ID of each shader
      unsigned int vertexShader;
      unsigned int fragmentShader;

      // ID of shader program
      unsigned int shaderProgram;

      // Current object to render
      Polytope* polytope;

      // Polytopes to choose from
      Hypercube hypercube;

      // The camera for viewing the world
      Camera camera;
      Camera4D camera4D;
      float standardCameraSpeed = Camera::SPEED;
      float alternateCameraSpeed = Camera::SPEED * 5;
      float* cameraSpeed = &standardCameraSpeed;
      float fieldOfVision = 45.f;
      float viewDistance = 150.f;

      // Toggleable editor windows and features
      bool showWireframe = false;
      bool show3DCameraWindow = true;
      bool show4DCameraWindow = true;
      bool showTransformWindow = true;
      bool showPolytopeInfoWindow = true;
      bool showDemoWindow = false;

      // Rotation helpers
      bool spinFirstRotation = false;
      float firstRotationAngle = 0.f;
      float firstRotationSpeed = 1.f;
      float firstRotationOffset = 0.f;
      bool spinSecondRotation = false;
      float secondRotationAngle = 0.f;
      float secondRotationSpeed = 1.f;
      float secondRotationOffset = 0.f;

      // Create rotation widget for imgui
      static void tweakRotation(float& angle, bool& spin, float& base, 
          float& offset, float& speed);

      // Place camera back into a normal position
      void resetCameraPosition();
  };
}

#endif
