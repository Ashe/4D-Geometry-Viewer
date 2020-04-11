// Hyperoctahedron.cpp
// A class storing a 16-cell polytope

#include "Hyperoctahedron.h"

// Constructor
App::Hyperoctahedron::Hyperoctahedron() {

  // Generate vertices
  vertices = new float[8 * 4];
  unsigned int vertexCount = 0;

  // Create a tetracross
  for (unsigned int j = 0; j < 4; ++j) {
    for (int val = -1; val < 2; val += 2) {
      for (unsigned int i = 0; i < 4; ++i) {
        vertices[vertexCount++] = i == j ? (float)val : 0.f;
        printf("%f\n", vertices[vertexCount - 1]);
      }
      printf("break\n");
    }
  }

  // Generate indices
  indices = new unsigned int[24 * 2];
  unsigned int indexCount = 0;

  // Connect tetracross vertices (ignoring opposite pairs)
  for (unsigned int j = 0; j < 8; ++j) {
    for (unsigned int i = j + 1 + ((j + 1) % 2); i < 8; ++i) {
      indices[indexCount++] = j;
      indices[indexCount++] = i;
      printf("Edge %u: (%u -> %u)\n", indexCount / 2, 
          indices[indexCount - 2], indices[indexCount - 1]);
    }
  }
  printf("Index count: %u\n", indexCount);

  // Push generated vertices to these buffers
  updateVertices(GL_LINES, vertexCount, indexCount);
}

// Show information about the hyperoctahedron
void 
App::Hyperoctahedron::showPolytopeInfo() {

}
