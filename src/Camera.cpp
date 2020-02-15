// Camera.cpp
// Functionality for controlling the user's perspective

#include "Camera.h"

// Constructor with vectors
App::Camera::Camera(glm::vec3 pos, glm::vec3 up, 
    float startYaw, float startPitch)
    : forward(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), 
      mouseSensitivity(SENSITIVITY), zoom(ZOOM) {
  position = pos;
  worldUp = up;
  yaw = startYaw;
  pitch = startPitch;
  updateCameraVectors();
}

// Constructor with scalar values
App::Camera::Camera(float posX, float posY, float posZ, 
    float upX, float upY, float upZ, float startYaw, float startPitch) 
    : forward(glm::vec3(0.0f, 0.0f, -1.0f)), 
      movementSpeed(SPEED), 
      mouseSensitivity(SENSITIVITY), zoom(ZOOM) {
  position = glm::vec3(posX, posY, posZ);
  worldUp = glm::vec3(upX, upY, upZ);
  yaw = startYaw;
  pitch = startPitch;
  updateCameraVectors();
}

// Returns a matrix calculated using Euler Angles and LookAt Matrix
glm::mat4 
App::Camera::getViewMatrix() const {
  return glm::lookAt(position, position + forward, up);
}

// Processes input received from any keyboard-like input system
void 
App::Camera::move(Movement direction, float deltaTime) {
  float velocity = movementSpeed * deltaTime;
  switch (direction) {
    case FORWARD:   position += forward * velocity; break;
    case BACKWARD:  position -= forward * velocity; break;
    case LEFT:      position -= right   * velocity; break;
    case RIGHT:     position += right   * velocity; break;
    case UP:        position += up      * velocity; break;
    case DOWN:      position -= up      * velocity; break;
    default: break;
  }
}

// Processes input received from a mouse input system
void 
App::Camera::turn(float xoffset, float yoffset, 
    GLboolean constrainPitch) {

  // Rotate the camera using the mouse
  xoffset *= mouseSensitivity;
  yoffset *= - mouseSensitivity;
  yaw   += xoffset;
  pitch += yoffset;

  // Make sure that when pitch is out of bounds, screen doesn't get flipped
  if (constrainPitch) {
    if (pitch > 89.0f) {
      pitch = 89.0f;
    }
    if (pitch < -89.0f) {
      pitch = -89.0f;
    }
  }

  // Update Front, Right and Up Vectors using the updated Euler angles
  updateCameraVectors();
}

// Processes input received from a mouse scroll-wheel event
void 
App::Camera::zoomIn(float yoffset) {
  if (zoom >= 1.0f && zoom <= 45.0f) {
    zoom -= yoffset;
  }
  else if (zoom < 1.0f) {
    zoom = 1.0f;
  }
  else if (zoom > 45.0f) {
    zoom = 45.0f;
  }
}

// Calculates the forward vector from the Camera's (updated) Euler Angles
void 
App::Camera::updateCameraVectors() {

  // Calculate the new Front vector
  forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  forward.y = sin(glm::radians(pitch));
  forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  // Normalize the vectors, because their length gets closer to 0 
  // the more you look up or down which results in slower movement.
  forward = glm::normalize(forward);

  // Also re-calculate the Right and Up vector
  right = glm::normalize(glm::cross(forward, worldUp));  
  up    = glm::normalize(glm::cross(right, forward));
}
