// Engine.h
// A class for handling updating and rendering

#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <stdio.h>

#include <glbinding/glbinding.h>
#include <glbinding/gl/gl.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <imgui.h>

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace App {

  class Scene;

  // Core class of the program
  // Handles the main loop of the application
  class Engine {

    public:

      // The colour to clear the window with
      ImVec4 clearColour = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

      // Create a window and start the engine
      bool initialise(
          int width = 1280, int height = 720, const char* title = "App"); 

      // Give the engine a scene to use
      void switchScene(Scene* s);

      // Start the game loop
      void start();

      // Get a pointer to the window
      GLFWwindow* getWindow() const;

      // Get whether input should be accepted by scenes
      bool getAcceptKeyboardInput() const;
      bool getAcceptMouseInput() const;

      // Get the aspect ratio of the window
      float getAspectRatio() const;

      // Get the error code if there is one
      int getErrorCode() const;

    private:

      // Pointer to current window
      GLFWwindow* window = nullptr;

      // Pointer to the current scene to use
      Scene* scene = nullptr;

      // Whether scenes should process input
      bool acceptKeyboardInput = true;
      bool acceptMouseInput = true;

      // Store the last reported error code
      int error = 0;

      // Send key inputs to application
      static void keyInputCallback(GLFWwindow* window, 
          int key, int scancode, int action, int mods);

      // Send mouse button inputs to application
      static void mouseButtonInputCallback(GLFWwindow* window,
          int button, int action, int mods);

      // Send mouse scrolling inputs to application
      static void mouseScrollInputCallback(GLFWwindow* window,
          double xoffset, double yoffset);

      // Report any errors that occur
      static void handleError(int code, const char* description);

  };
}

#endif
