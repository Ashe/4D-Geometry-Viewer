// Engine.cpp
// A class for handling updating and rendering

#include "Engine.h"
#include "Scene.h"

// Create a window and start the engine
bool
App::Engine::initialise(int w, int h, const char* title) {

  // Enable error reporting
  glfwSetErrorCallback(&App::Engine::handleError);

  // Initialise GLFW
  if (!glfwInit()) {
    error = 1;
    fprintf(stderr, "[Error] GLFW initialisation failed.\n");
    return false;
  }

  // Decide GL+GLSL versions
#if __APPLE__
  // GL 3.2 + GLSL 150
  const char* glsl_version = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
  // GL 3.0 + GLSL 130
  const char* glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  // 3.2+ Only
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // 3.0+ only
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // Create window with graphics context
  window = glfwCreateWindow(w, h, title, nullptr, nullptr);

  // Terminate program if window creation failed
  if (window == nullptr) {
    error = 2;
    fprintf(stderr, "[Error] Window creation failed.\n");
    return false;
  }

  // Specify that the current thread should use the window's context
  glfwMakeContextCurrent(window);

  // Enable vsync
  glfwSwapInterval(0);

  // Provide GLFW with input callback functions
  glfwSetWindowUserPointer(window, this);
  glfwSetKeyCallback(window, &Engine::keyInputCallback);
  glfwSetMouseButtonCallback(window, &Engine::mouseButtonInputCallback);
  glfwSetScrollCallback(window, &Engine::mouseScrollInputCallback);

  // Initialize OpenGL loader
  bool err = gladLoadGL() == 0;
  if (err) {
    error = 3;
    fprintf(stderr, "[Error] OpenGL loader initialisation failed.\n");
    return false;
  }

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

  // Setup Dear ImGui style
  ImGui::StyleColorsClassic();

  // Setup Platform/Renderer bindings
  // Also append event callbacks
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  // Report that initialisation was successful
  return true;
}

// Give the engine a scene to use
void
App::Engine::switchScene(App::Scene* s) {

  // Switch from previous scene
  if (scene != nullptr) {
    scene->switchFrom();
  }

  // Change the scene
  scene = s;

  // Notify new scene that it is now current
  if (scene != nullptr) {
    scene->switchTo();
  }
}

// Start the game loop
void
App::Engine::start() {

  // Get how long GLFW has elapsed for
  double elapsed = glfwGetTime();

  // Determine whether the game should loop
  bool remainOpen = !glfwWindowShouldClose(window) &&
      scene != nullptr;

  // Main loop
  while (remainOpen) {

    // Poll and handle events (inputs, window resize, etc.)
    // - When io.WantCaptureMouse is true, don't give dispatch to app
    // - When io.WantCaptureKeyboard is true, don't dispatch to app
    // Generally you may always pass all inputs to dear imgui
    // and hide them from your application based on those two flags.
    ImGuiIO& io = ImGui::GetIO();
    acceptKeyboardInput = !io.WantCaptureKeyboard;
    acceptMouseInput = !io.WantCaptureMouse;
    glfwPollEvents();

    // Calculate delta time and update elapsed time
    const double currentElapsed = glfwGetTime();
    const double deltaTime = currentElapsed - elapsed;
    elapsed = currentElapsed;

    // Update the current scene
    scene->update(deltaTime);

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Allow the scene to use imgui
    scene->handleImgui();

    // Set the viewport size
    int displayW, displayH;
    glfwGetFramebufferSize(window, &displayW, &displayH);
    glViewport(GLint(0), GLint(0), GLsizei(displayW), GLsizei(displayH));

    // Clear the viewport
    glClearColor(clearColour.x, clearColour.y, clearColour.z, clearColour.w);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render the scene
    scene->render();

    // Render imgui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Show the rendered frame in the window
    glfwSwapBuffers(window);

    // Determine whether the game should loop
    remainOpen = !glfwWindowShouldClose(window) &&
        scene != nullptr;
  }

  // Shutdown imgui
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  // Close the window
  glfwDestroyWindow(window);
  window = nullptr;

  // Terminate GLFW
  glfwTerminate();
}

// Get a pointer to the window
GLFWwindow* 
App::Engine::getWindow() const {
  return window;
}

// Get whether keyboard input should be accepted by scenes
bool
App::Engine::getAcceptKeyboardInput() const {
  return acceptKeyboardInput;
}

// Get whether mouse input should be accepted by scenes
bool
App::Engine::getAcceptMouseInput() const {
  return acceptMouseInput;
}

// Get the aspect ratio of the window
float
App::Engine::getAspectRatio() const {
  int displayW, displayH;
  glfwGetFramebufferSize(window, &displayW, &displayH);
  return (float)displayW / (float)displayH;
}

// Return the last reported error
int
App::Engine::getErrorCode() const {
  return error;
}

// Send key inputs to application
void
App::Engine::keyInputCallback(GLFWwindow* window,
    int key, int scancode, int action, int mods) {
  Engine* engine = (Engine*)glfwGetWindowUserPointer(window);
  if (engine != nullptr 
      && engine->acceptKeyboardInput
      && engine->scene != nullptr) {
    engine->scene->handleKeyboardInput(key, scancode, action, mods);
  }
}

// Send mouse button inputs to application
void
App::Engine::mouseButtonInputCallback(GLFWwindow* window,
    int button, int action, int mods) {
  Engine* engine = (Engine*)glfwGetWindowUserPointer(window);
  if (engine != nullptr 
      && engine->acceptMouseInput 
      && engine->scene != nullptr) {
    engine->scene->handleMouseButtonInput(button, action, mods);
  }
}

// Send mouse scrolling inputs to application
void 
App::Engine::mouseScrollInputCallback(GLFWwindow* window,
    double xoffset, double yoffset) {
  Engine* engine = (Engine*)glfwGetWindowUserPointer(window);
  if (engine != nullptr 
      && engine->acceptMouseInput 
      && engine->scene != nullptr) {
    engine->scene->handleMouseScrollInput(xoffset, yoffset);
  }
}

// Report any errors that occur
void
App::Engine::handleError(int code, const char* description) {
  fprintf(stderr, "[Error] GLFW code %d: %s\n", code, description);
}
