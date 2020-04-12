// Polytope.cpp
// A base class for all polytope objects

#include "Polytope.h"

// Constructor
App::Polytope::Polytope() {

  // Generate default transform
  resetTransform();

  // Generate vertex array object and buffers
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
}

// Destructor
App::Polytope::~Polytope() {

  // Tell OpenGL to delete buffers
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteVertexArrays(1, &VAO);

  // Delete index data
  if (indices != nullptr) {
    delete[] indices;
    indices = nullptr;
  }

  // Delete vertex data
  if (vertices != nullptr) {
    delete[] vertices;
    vertices = nullptr;
  }
}

// Render the polytope
void
App::Polytope::render() {

  // Ensure that there is enough information to render the object
  if (vertices == nullptr || indices == nullptr ||
      vertexCount == 0 || indexCount == 0) {
    printf("[Error] Polytope vertices or indices not initialised.\n");
    return;
  }

  // Bind VAO so that OpenGL knows what data to render
  glBindVertexArray(VAO);

  // Draw the tesseract
  glDrawElements(mode, indexCount, GL_UNSIGNED_INT, 0);

  // Unbind VAO
  glBindVertexArray(0);
}

// Recreate the transformation matrix
void 
App::Polytope::updateTransform() {

  // Start with identity matrix
  for (unsigned int j = 0; j < 5; ++j) {
    for (unsigned int i = 0; i < 5; ++i) {
      transform[j][i] = i == j ? 1.f : 0.f;
    }
  }

  // Recreate translation matrix
  for(unsigned int j = 0; j < 5; ++j) {
    for(unsigned int i = 0; i < 5; ++i) {
      if (i == j) {
        translationMatrix[j][i] = 1.f;
      }
      else if (i == 4) {
        switch (j) {
          case 0: translationMatrix[j][i] = position.x; break;
          case 1: translationMatrix[j][i] = position.y; break;
          case 2: translationMatrix[j][i] = position.z; break;
          case 3: translationMatrix[j][i] = position.w; break;
          default:  printf("[Error] Invalid index in translation matrix.\n");
        }
      }
      else {
        translationMatrix[j][i] = 0.f;
      }
    }
  }

  // Recreate scale matrix
  for(unsigned int j = 0; j < 5; ++j) {
    for(unsigned int i = 0; i < 5; ++i) {
      switch (i + j * 5) {
        case 0:   scaleMatrix[j][i] = scale.x; break;
        case 6:   scaleMatrix[j][i] = scale.y; break;
        case 12:  scaleMatrix[j][i] = scale.z; break;
        case 18:  scaleMatrix[j][i] = scale.w; break;
        case 24:  scaleMatrix[j][i] = 1.f; break;
        default:  scaleMatrix[j][i] = 0.f; break;
      }
    }
  }

  // Recreate rotation matrices
  for(unsigned int j = 0; j < 5; ++j) {
    for(unsigned int i = 0; i < 5; ++i) {
      rotationMatrix[j][i] = i == j ? 1.f : 0.f;
    }
  }
  
  // Rotate the polytope depending on rotation type 
  switch (rotationType) {
    case RotationType::XY:
      applyRotation(firstRotation, 0, 1);
      if (enableDoubleRotation) {
        applyRotation(secondRotation, 2, 3);
      }
      break;
    case RotationType::XZ:
      applyRotation(firstRotation, 0, 2);
      if (enableDoubleRotation) {
        applyRotation(secondRotation, 1, 3);
      }
      break;
    case RotationType::XW:
      applyRotation(firstRotation, 0, 3);
      if (enableDoubleRotation) {
        applyRotation(secondRotation, 1, 2);
      }
      break;
    case RotationType::YZ:
      applyRotation(firstRotation, 1, 2);
      if (enableDoubleRotation) {
        applyRotation(secondRotation, 0, 3);
      }
      break;
    case RotationType::YW:
      applyRotation(firstRotation, 1, 3);
      if (enableDoubleRotation) {
        applyRotation(secondRotation, 0, 2);
      }
      break;
    case RotationType::ZW:
      applyRotation(firstRotation, 2, 3);
      if (enableDoubleRotation) {
        applyRotation(secondRotation, 0, 1);
      }
      break;
  }

  // Validate shear coordinates
  if (shearX < -1 || shearX > 4) { shearX = -1; }
  if (shearY < -1 || shearY > 4) { shearY = -1; }

  // Recreate shear matrix
  for(unsigned int j = 0; j < 5; ++j) {
    for(unsigned int i = 0; i < 5; ++i) {

      // Identity along diagonal
      if (i == j) {
        shearMatrix[j][i] = 1.f;
      }

      // When shear x and y are different, insert shear value
      else if (i == shearX && j == shearY) {
        shearMatrix[j][i] = shearValue;
      }
      
      // 0 otherwise
      else {
        shearMatrix[j][i] = 0.f;
      }
    }
  }

  // Combine matrices to make transform
  mult(transform, translationMatrix, transform);
  mult(transform, rotationMatrix, transform);
  mult(transform, scaleMatrix, transform);
  mult(transform, shearMatrix, transform);
}

// Reset all transformations for this polytope
void
App::Polytope::resetTransform() {

  // Reset transform values to sane defaults
  position = glm::vec4(0.f, 0.f, 0.f, 0.f);
  scaleTarget = glm::vec4(1.f, 1.f, 1.f, 1.f);
  firstRotation = 0.f;
  secondRotation = 0.f;
  enableDoubleRotation = false;
  shearX = -1;
  shearY = -1;
  shearValue = 0;

  // Recreate the transform using these new values
  updateTransform();
}

// Get this polytope's transform
float* 
App::Polytope::getTransform() const{
  return (float*)transform;
}

// Push vertices to buffers for rendering
void 
App::Polytope::updateVertices(unsigned int renderMode, 
    unsigned int vcount, unsigned int icount) {

  // Only do this when vertex and index data is present
  if (vertices == nullptr || indices == nullptr) {
    printf("[Error] Polytope vertices or indices not initialised.\n");
    return;
  }

  // Use the amount of vertices and indices for rendering
  vertexCount = vcount;
  indexCount = icount;

  // Set the render mode
  mode = renderMode;

  // Bind vertex array object in preperation for pushing vertices
  glBindVertexArray(VAO);

  // Bind and copy vertices into vertex buffer
  unsigned int size = vertexCount * sizeof(float);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

  // Bind and copy indices into element buffer
  size = indexCount * sizeof(unsigned int);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

  // Tell OpenGL how the data in vertices relates to shader code
  constexpr unsigned int fsize = sizeof(float);

  // location = 0: vertex position with x, y, z, w (stride of 4, no offset)
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, fsize * 4, (void*)0);
  glEnableVertexAttribArray(0);

  // Unbind VAO until needed
  glBindVertexArray(0);
}

// Multiply two 5x5 matrices together
void
App::Polytope::mult(float out[5][5], float a[5][5], float b[5][5]) {

  // Define temporary vector
  std::vector<std::vector<float>> temp(5);

  // Iterate through all elements
  for (unsigned int j = 0; j < 5; ++j) {
    temp[j] = std::vector<float>(5);
    for (unsigned int i = 0; i < 5; ++i) {
      temp[j][i] = 0;
      for (unsigned int k = 0; k < 5; ++k) {
        temp[j][i] += a[k][i] * b[j][k];
      }
    }
  }

  // Return the variables in the temporary vector
  for (unsigned int j = 0; j < 5; ++j) {
    for (unsigned int i = 0; i < 5; ++i) {
      out[j][i] = temp[j][i];
    }
  }
}

// Rotate around any plane
void
App::Polytope::applyRotation(float angle, unsigned int a, unsigned int b) {
  const float c = glm::cos(angle);
  const float s = glm::sin(angle);
  rotationMatrix[a][a] = c;
  rotationMatrix[a][b] = -s;
  rotationMatrix[b][a] = s;
  rotationMatrix[b][b] = c;
}
