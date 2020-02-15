// Camera.h
// Functionality for controlling the user's perspective

#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace App {

  // An abstract camera class that processes input 
  // Calculates the corresponding Euler Angles, Vectors and Matrices
  class Camera {

    public:

      // Define default camera values
      static constexpr float YAW = -90.0f;
      static constexpr float PITCH = 0.0f;
      static constexpr float SPEED = 10.f;
      static constexpr float SENSITIVITY = 0.1f;
      static constexpr float ZOOM = 45.0f;

      // Defines several possible options for camera movement
      enum Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
      };

      // Constructor with vectors
      Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
          glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
          float yaw = YAW, 
          float pitch = PITCH);

      // Constructor with scalar values
      Camera(float posX, float posY, float posZ, 
          float upX, float upY, float upZ, float yaw, float pitch);

      // Camera Attributes
      glm::vec3 position;
      glm::vec3 forward;
      glm::vec3 up;
      glm::vec3 right;
      glm::vec3 worldUp;

      // Euler Angles
      float yaw;
      float pitch;

      // Camera options
      float movementSpeed;
      float mouseSensitivity;
      float zoom;

      // Returns a matrix calculated using Euler Angles and LookAt Matrix
      glm::mat4 getViewMatrix() const;

      // Processes input received from any keyboard-like input system
      void move(Movement direction, float deltaTime);

      // Processes input received from a mouse input system
      void turn(float xoffset, float yoffset, GLboolean constrainPitch = true);

      // Processes input received from a mouse scroll-wheel event
      void zoomIn(float yoffset);

      // Calculates the forward vector from the Camera's (updated) Euler Angles
      void updateCameraVectors();

  };
}

#endif
