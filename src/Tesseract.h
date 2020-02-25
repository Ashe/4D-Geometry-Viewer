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

      // Transform of this object
      float transform[5][5];

      // Push vertices to buffers for rendering
      void updateVertices();

      // Render the Tesseract
      void render();

      // Reset the transform for this object
      void resetTransform();

    private:

      // Vertices and indices of tesseract
      unsigned int vertexCount, indexCount;
      float* vertices = nullptr;
      unsigned int* indices = nullptr;

      // IDs of buffers
      unsigned int VBO, EBO, VAO;
  };
}

#endif
