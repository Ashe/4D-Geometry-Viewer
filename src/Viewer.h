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
#include "Tesseract.h"
#include "shaders/Vertex.h"
#include "shaders/Fragment.h"

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
      std::unique_ptr<Tesseract> object;

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
      bool showCameraWindow = true;
      bool showDemoWindow = false;

      // Place camera back into a normal position
      void resetCameraPosition();
  };
}

#endif
