// Viewer.cpp
// A scene used to view geometry

#include "Viewer.h"

// Constructor
App::Viewer::Viewer(Engine& e) : Scene(e) {

  /////////////
  // SHADERS //
  /////////////

  // Create and compile vertex shader
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &App::Shaders::vertexSource, NULL);
  glCompileShader(vertexShader);

  // Check for any errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("[Error] Failed to compile vertex shader.\n - %s\n", infoLog);
  }

  // Create and compile fragment shader
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &App::Shaders::fragmentSource, NULL);
  glCompileShader(fragmentShader);

  // Check for any errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    printf("[Error] Failed to compile fragment shader.\n - %s\n", infoLog);
  }

  // Create a shader program from the vertex and fragment shaders
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // Check for any errors in the shaders
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if(!success) {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      printf("[Error] Failed to link shader program.\n - %s\n", infoLog);
  }

  // Delete shader objects now they aren't in use
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  ////////////
  // Viewer //
  ////////////

  // Intialise the camera
  camera = Camera(glm::vec3(0.f, 1.f, 5.f));

  // Initialise tesseract
  object = std::make_unique<Tesseract>();
}

// Handle keyboard input for keybindings
void 
App::Viewer::handleKeyboardInput(int key, int scan, int action, int mods) {

  // Handle keypresses
  if (action == GLFW_PRESS) {

    // Control modifier keybindings
    if (mods == GLFW_MOD_CONTROL) {
      switch(key) {
        case GLFW_KEY_W: showWireframe ^= 1; break;
      }
    }

    // Control + Shift modifier keybindings
    if ((mods & GLFW_MOD_CONTROL) && (mods & GLFW_MOD_SHIFT)) {
      switch(key) {
      }
    }
  }
}

// Alter the speed of the camera
void 
App::Viewer::handleMouseScrollInput(double x, double y) {
}

// Update the viewer
void 
App::Viewer::update(double dt) {

  // Get window from the engine
  GLFWwindow* window = engine.getWindow();
  if (window == nullptr) {
    return;
  }

  // Only interpret mouse input if necessary
  if (engine.getAcceptMouseInput()) {

    // Store x and y position of mouse
    static float xPos, yPos;
    double tempXPos, tempYPos;
    glfwGetCursorPos(window, &tempXPos, &tempYPos);

    // Look around with the right mouse button
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)) {

      // Hide the mouse
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

      // Rotate the camera based on changes in the mouse's position
      camera.turn(tempXPos - xPos, tempYPos - yPos);
    }

    // If the mouse isn't held, return cursor to normal
    else {
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    // Update the x and y position of the mouse
    xPos = tempXPos;
    yPos = tempYPos;
  }

  // Set cursor to normal otherwise
  else {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }

  // Only interpret keyboard input if necessary
  if (engine.getAcceptKeyboardInput()) {

    // Alternate the camera's speed with shift key
    cameraSpeed = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS
        ? &alternateCameraSpeed : &standardCameraSpeed;
    if (cameraSpeed != nullptr) {
      camera.movementSpeed = *cameraSpeed;
    }

    // Move the camera with the keyboard when not holding control
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) != GLFW_PRESS) {
      if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.move(Camera::Movement::LEFT, dt);
      }
      if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.move(Camera::Movement::RIGHT, dt);
      }
      if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.move(Camera::Movement::FORWARD, dt);
      }
      if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.move(Camera::Movement::BACKWARD, dt);
      }
      if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.move(Camera::Movement::UP, dt);
      }
      if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        camera.move(Camera::Movement::DOWN, dt);
      }
    }
  }
}

// Render geometry
void
App::Viewer::render() {

  // Get the view matrix from the camera
  glm::mat4 view = camera.getViewMatrix();

  // Create projection matrix
  glm::mat4 projection;
  projection = glm::perspective(
      glm::radians(fieldOfVision), 
      engine.getAspectRatio(), 0.1f, viewDistance);

  // Give view matrix to vertex shader
  const int viewLoc = glGetUniformLocation(shaderProgram, "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

  // Give projection matrix to vertex shader
  const int projLoc = glGetUniformLocation(shaderProgram, "projection");
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

  // Show wireframes when enabled
  glPolygonMode(GL_FRONT_AND_BACK, showWireframe ? GL_LINE : GL_FILL);

  // Choose a shader
  glUseProgram(shaderProgram);

  // Render the tesseract
  if (object != nullptr) {

    // Give OpenGL transform of object
    const int trans = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(trans, 1, GL_FALSE, glm::value_ptr(object->transform));

    // Render object
    object->render();
  }
}

// Grant the viewer access to imgui
void 
App::Viewer::handleImgui() {

  // Scale of the environment for speed / distance
  unsigned int scale = 1;

  // Main menu bar
  if (ImGui::BeginMainMenuBar()) {

    // File menu
    if (ImGui::BeginMenu("File")) {
      ImGui::EndMenu();
    }

    // View menu
    if (ImGui::BeginMenu("View")) {
      ImGui::MenuItem("Show wireframes", "CTRL + W", &showWireframe);
      ImGui::MenuItem("Camera properties", NULL, &showCameraWindow);
      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }

  // Show camera settings
  if (showCameraWindow) {
    if (ImGui::Begin("Camera Properties", &showCameraWindow)) {
      ImGui::Text("Location:");
      glm::vec3 pos = camera.position;
      pos /= scale > 0.f ? (float)scale : 1.f;
      ImGui::PushItemWidth(60);
      ImGui::DragFloat("X##camX", &pos.x, 1.f);
      ImGui::SameLine();
      ImGui::DragFloat("Y##camY", &pos.y, 1.f);
      ImGui::SameLine();
      ImGui::DragFloat("Z##camZ", &pos.z, 1.f);
      camera.position = pos * (scale > 0.f ? (float)scale : 1.f);
      ImGui::DragFloat("Pitch", &camera.pitch, 1.f);
      ImGui::SameLine();
      ImGui::DragFloat("Yaw", &camera.yaw, 1.f);
      ImGui::DragFloat("Speed", &standardCameraSpeed, 1.f, 1.f, 100.f);
      ImGui::SameLine();
      ImGui::DragFloat("Alt speed", 
          &alternateCameraSpeed, 1.f, 1.f, 100.f);
      ImGui::DragFloat("FOV", &fieldOfVision, 1.f, 30.f, 110.f);
      ImGui::DragFloat("View Distance", &viewDistance, 1.f, 1.f, 1000.f);
      ImGui::PopItemWidth();
      ImGui::Spacing();
      ImGui::ColorEdit3("Clear colour", (float*)&engine.clearColour);
      ImGui::Spacing();
      if (ImGui::Button("Reset position")) {
        resetCameraPosition();
      }
      ImGui::End();
    }
  }

  // Show imgui demo
  if (showDemoWindow) {
    ImGui::ShowDemoWindow(&showDemoWindow);
  }
}

// Place camera back into a normal position
void
App::Viewer::resetCameraPosition() {
  camera.position = glm::vec3(0.f, 0.f, 0.f);
}
