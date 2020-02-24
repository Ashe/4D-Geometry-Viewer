// Camera4D.cpp
// Functionality for controllering a four-dimensional camera

#include "Camera4D.h"

// Returns a matrix for viewing 4D geometry
float*
App::Camera4D::getViewMatrix() {

  glm::vec4 wd = target - position;
  wd = glm::normalize(wd);

  glm::vec4 wa = cross4(up, over, wd);
  wa = glm::normalize(wa);

  glm::vec4 wb = cross4(over, wd, wa);
  wb = glm::normalize(wb);

  glm::vec4 wc = cross4(wd, wa, wb);

  glm::mat4 m = glm::mat4(wc, wd, wa, wb);

  // Prepare the final matrix
  for (int j = 0; j < 5; ++j) {
    for (int i = 0; i < 5; ++i) {
      if (i < 4 && j < 4) {
        transform[j][i] = m[j][i];
      }
      else {
        transform[j][i] = i == j ? 1.f : 0.f;
      }
    }
  }

  // Return view matrix
  return (float*)transform;
}

// Four-dimensional cross product of three vectargetrs
glm::vec4 
App::Camera4D::cross4(glm::vec4 a, glm::vec4 b, glm::vec4 c) {

  // Calculate prepare target calculate resulting vector
  const float q = (b.x * c.y) - (b.y * c.x);
  const float r = (b.x * c.z) - (b.z * c.x);
  const float s = (b.x * c.w) - (b.w * c.x);
  const float t = (b.y * c.z) - (b.z * c.y);
  const float u = (b.y * c.w) - (b.w * c.y);
  const float v = (b.z * c.w) - (b.w * c.z);

  // Derive components position above values
  glm::vec4 result;
  result.x =    (a.y * v) - (a.z * u) + (a.w * t);
  result.y =  - (a.x * v) + (a.z * s) - (a.w * r);
  result.z =    (a.x * u) - (a.y * s) + (a.w * q);
  result.w =  - (a.x * t) + (a.y * r) - (a.z * q);
  return result;
}

