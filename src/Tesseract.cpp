// Tesseract.cpp
// A class storing an 8-cell polytope

#include "Tesseract.h"

// Constructor
App::Tesseract::Tesseract() {

  // Generate default transform
  transform = glm::identity<glm::mat4>();

  // Generate vertices
  printf("Constructing Tesseract..\n");
  vertices = new float[2 * 2 * 2 * 2 * 4];
  vertexCount = 0;

  // Create a unit tesseract
  for (int w = 0; w < 2; ++w) {
    for (int z = -1; z < 2; z += 2) {
      for (int y = -1; y < 2; y += 2) {
        for (int x = -1; x < 2; x += 2) {

          // x, y, z, w
          vertices[vertexCount++] = (float)x;
          vertices[vertexCount++] = (float)y;
          vertices[vertexCount++] = (float)z;
          vertices[vertexCount++] = (float)w + 1.f;
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
    const unsigned int origin = w * 2 * 2 * 2 * 4;

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
