// Tesseract.h
// A class storing an 8-cell polytope 

#ifndef TESSERACT_H
#define TESSERACT_H

#include "Engine.h"

namespace App {

  // Store information necessary to render a 4D cube
  class Tesseract {

    public:

      // Constructors
      Tesseract();
      Tesseract(const Tesseract&) = delete;
      ~Tesseract();

      // Transform values
      glm::vec4 scale;

      // Push vertices to buffers for rendering
      void updateVertices();

      // Render the Tesseract
      void render();

      // Recreate the transformation matrix
      void updateTransform(double dt = 0.0);

      // Reset transform values for this object
      void resetTransform();

      // Get the transform matrix of the object based on values
      float* getTransform() const;

    private:

      // Vertices and indices of tesseract
      unsigned int vertexCount, indexCount;
      float* vertices = nullptr;
      unsigned int* indices = nullptr;

      // IDs of buffers
      unsigned int VBO, EBO, VAO;

      // Transform of this object
      float transform[5][5];
      float scaleMatrix[5][5];

      // Multiply two 5x5 matrices together
      static void mult(float out[5][5], float a[5][5], float b[5][5]);
  };
}

#endif
