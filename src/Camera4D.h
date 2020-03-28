// Camera4D.h
// Functionality for controllering a four-dimensional camera

#ifndef CAMERA_4D_H
#define CAMERA_4D_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace App {

  // Class that perceives the 4D world
  class Camera4D {

    public:

      // Configuration of this camera
      glm::vec4 position = glm::vec4(0.f, 0.f, 0.f, 0.f);
      glm::vec4 target = glm::vec4(0.f, 0.f, 0.f, 1.f);
      glm::vec4 up = glm::vec4(0.f, 1.f, 0.f, 0.f);
      glm::vec4 over = glm::vec4(0.f, 0.f, 1.f, 0.f);

      // Returns a matrix for viewing 4D geometry
      float* getViewMatrix();

    private:

      // The view matrix to be retrieved from this camera
      float transform[5][5];

      // Four-dimensional cross product of three vectors
      static glm::vec4 cross4(glm::vec4 a, glm::vec4 b, glm::vec4 c);
  };
}

#endif
