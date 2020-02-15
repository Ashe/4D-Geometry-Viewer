// Viewer.h
// A scene used to view geometry

#ifndef EDITOR_H
#define EDITOR_H

#include "Scene.h"
#include "Camera.h"

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

      // Vertex shader source code
      const char *vertexShaderSource = "#version 330 core\n"
          "layout (location = 0) in vec3 aPos;\n"
          "uniform mat4 transform;\n"
          "uniform mat4 view;\n"
          "uniform mat4 projection;\n"
          "void main()\n"
          "{\n"
          "   gl_Position = projection * view * transform * vec4(aPos, 1.0);\n"
          "}\0";

      // Fragment shader source code
      const char *fragmentShaderSource = "#version 330 core\n"
          "out vec4 FragColor;\n"
          "void main()\n"
          "{\n"
              "FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
          "}\0";

      // ID of each shader
      unsigned int vertexShader;
      unsigned int fragmentShader;

      // ID of shader program
      unsigned int shaderProgram;

      // The camera for viewing the world
      Camera camera;
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
