// Tesseract.cpp
// A class storing an 8-cell polytope

#include "Tesseract.h"

// Constructor
App::Tesseract::Tesseract() {

  // Generate default transform
  resetTransform();

  // Generate vertices
  printf("Constructing Tesseract..\n");
  vertices = new float[2 * 2 * 2 * 2 * 4];
  vertexCount = 0;

  // Create a unit tesseract
  for (int w = 1; w < 3; ++w) {
    for (int z = -1; z < 2; z += 2) {
      for (int y = -1; y < 2; y += 2) {
        for (int x = -1; x < 2; x += 2) {

          // x, y, z, w
          vertices[vertexCount++] = (float)x;
          vertices[vertexCount++] = (float)y;
          vertices[vertexCount++] = (float)z;
          vertices[vertexCount++] = (float)w;
        }
      }
    }
  }

  // Record how many vertices were created
  printf("Generated %u vertices (16 expected)..\n", vertexCount / 4);

  // Generate indices (lines)
  indices = new unsigned int[100];
  indexCount = 0;

  // Connect all cube vertices
  for (int w = 0; w < 2; ++w) {

    // Find which cube this vertex belongs to (inner or outer)
    const unsigned int origin = w * 2 * 2 * 2;

    // Top face
    indices[indexCount++] = origin;
    indices[indexCount++] = origin + 1;
    indices[indexCount++] = origin + 1;
    indices[indexCount++] = origin + 3;
    indices[indexCount++] = origin + 3;
    indices[indexCount++] = origin + 2;
    indices[indexCount++] = origin + 2;
    indices[indexCount++] = origin;

    // Left face
    indices[indexCount++] = origin;
    indices[indexCount++] = origin + 4;
    indices[indexCount++] = origin + 4;
    indices[indexCount++] = origin + 6;
    indices[indexCount++] = origin + 6;
    indices[indexCount++] = origin + 2;

    // Right face
    indices[indexCount++] = origin + 1;
    indices[indexCount++] = origin + 5;
    indices[indexCount++] = origin + 5;
    indices[indexCount++] = origin + 7;
    indices[indexCount++] = origin + 7;
    indices[indexCount++] = origin + 3;

    // Bottom face
    indices[indexCount++] = origin + 4;
    indices[indexCount++] = origin + 5;
    indices[indexCount++] = origin + 6;
    indices[indexCount++] = origin + 7;
  }

  // Identify and connect vertices in both inner and outer cubes
  for (int z = 0; z < 2; ++z) {
    for (int y = 0; y < 2; ++y) {
      for (int x = 0; x < 2; ++x) {
        const unsigned int innerCube = x + (y * 2) + (z * 2 * 2);
        const unsigned int outerCube = innerCube + 2 * 2 * 2;
        indices[indexCount++] = innerCube;
        indices[indexCount++] = outerCube;
      }
    }
  }

  // Record how many indices were created
  printf("Generated %u indices (32 expected)..\n", indexCount / 2);

  // Generate vertex array object and buffers
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // Push generated vertices to these buffers
  updateVertices();
}

// Destructor
App::Tesseract::~Tesseract() {

  // Tell OpenGL to delete buffers
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteVertexArrays(1, &VAO);

  // Delete vertex and index data
  delete[] vertices;
  delete[] indices;
  vertices = nullptr;
  indices = nullptr;
}

// Push vertices to buffers for rendering
void 
App::Tesseract::updateVertices() {

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

// Render the tesseract
void
App::Tesseract::render() {

  // Ensure that there is enough information to render the object
  if (vertices == nullptr || indices == nullptr) {
    printf("[Error] Tesseract vertices or indices not initialised.\n");
    return;
  }

  // Bind VAO so that OpenGL knows what data to render
  glBindVertexArray(VAO);

  // Draw the tesseract
  glDrawElements(GL_LINES, indexCount, GL_UNSIGNED_INT, 0);

  // Unbind VAO
  glBindVertexArray(0);
}

// Recreate the transformation matrix
void 
App::Tesseract::updateTransform(double dt) {

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

  // Combine matrices to make transform
  mult(transform, translationMatrix, transform);
  mult(transform, scaleMatrix, transform);
}

// Reset transform values for this object
void
App::Tesseract::resetTransform() {

  // Reset transform values to sane defaults
  position = glm::vec4(0.f, 0.f, 0.f, 0.f);
  scale = glm::vec4(1.f, 1.f, 1.f, 1.f);

  // Recreate the transform using these new values
  updateTransform();
}

// Get the transform matrix of the object based on values
float* 
App::Tesseract::getTransform() const{
  return (float*)transform;
}

// Multiply two 5x5 matrices together
void
App::Tesseract::mult(float out[5][5], float a[5][5], float b[5][5]) {

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
