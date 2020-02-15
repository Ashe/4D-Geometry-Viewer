// main.cpp
// Entry point to program

#include "Engine.h"
#include "Viewer.h"

// Entry point
int main(int, char**) {

  // Prepare the engine
  App::Engine project;
  bool ready = project.initialise();

  // Only start the project if initialised
  if (!ready) {
    return 1;
  }

  // Create a scene to pass to the engine
  App::Viewer viewer(project);

  // Give the engine access to the scene
  project.switchScene(&viewer);

  // Start the engine
  project.start();

  // Exit with any errors that the project experienced
  return project.getErrorCode();
}
