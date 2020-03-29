// Polytope.h
// A base class for all polytope objects

#ifndef POLYTOPES_POLYTOPE_H
#define POLYTOPES_POLYTOPE_H

#include "../Engine.h"
#include "../RotationType.h"

namespace App {

  // Require all polytopes to have common aspects
  class Polytope {

    public:

      // Constructors
      Polytope();
      Polytope(const Polytope&) = delete;
      virtual ~Polytope();

      // Transform values
      glm::vec4 position;
      glm::vec4 scale;

      // Rotation values
      RotationType rotationType = RotationType::XY;
      bool enableDoubleRotation = false;
      float firstRotation = 0.f;
      float secondRotation = 0.f;

      // ImGui hook for showing info about the current polytope
      virtual void showPolytopeInfo() = 0;

      // Render the polytope
      void render();

      // Recreate the transformation matrix
      void updateTransform();

      // Reset all transformations for this polytope
      void resetTransform();

      // Get this polytope's transform
      float* getTransform() const;

    protected:

      // Vertices and indices of polytope
      float* vertices = nullptr;
      unsigned int* indices = nullptr;

      // Push vertices to buffers for rendering
      void updateVertices(unsigned int renderMode, 
          unsigned int vcount, unsigned int icount);

    private:

      // Internal counts of how many vertices and indices to render
      unsigned int vertexCount = 0;
      unsigned int indexCount = 0;

      // How should vertices be rendered
      unsigned int mode;

      // IDs of buffers
      unsigned int VBO, EBO, VAO;

      // Transform of this polytope
      float transform[5][5];
      float translationMatrix[5][5];
      float scaleMatrix[5][5];
      float rotationMatrix[5][5];

      // Multiply two 5x5 matrices together
      static void mult(float out[5][5], float a[5][5], float b[5][5]);

      // Modify rotation matrix for specific planes
      void applyRotation(float angle, unsigned int axisA, unsigned int axisB);

  };
}

#endif
