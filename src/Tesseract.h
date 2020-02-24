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
      glm::mat4 transform;

      // Push vertices to buffers for rendering
      void updateVertices();

      // Render the Tesseract
      void render();

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
