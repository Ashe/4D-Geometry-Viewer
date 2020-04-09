// Hypercube.cpp
// A class storing an 8-cell polytope

#include "Hypercube.h"

// Constructor
App::Hypercube::Hypercube() : Polytope() {

  // Generate vertices
  vertices = new float[2 * 2 * 2 * 2 * 4];
  unsigned int vertexCount = 0;

  // Create a tesseract
  for (int w = -1; w < 2; w += 2) {
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

  // Generate indices (lines)
  indices = new unsigned int[32 * 2];
  unsigned int indexCount = 0;

  // Connect all tesseract vertices
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

  // Push generated vertices to these buffers
  updateVertices(GL_LINES, vertexCount, indexCount);
}

// Show information about the hypercube
void
App::Hypercube::showPolytopeInfo() {

  // Prepare to show types of hypercubes
  static bool showTechnicalNames = false;

  // Show table of hypercubes
  ImGui::Columns(6, NULL, true);
  ImGui::SetColumnWidth(0, 155.0f);
  ImGui::Separator();
  ImGui::Text("Hypercube");
  ImGui::NextColumn();

  // Show all dimension numbers
  for (unsigned int i = 0; i < 6 - 1; ++i) {
    ImGui::SetColumnWidth(1 + i, 60.0f);
    ImGui::Text("%c", '0' + i);
    ImGui::NextColumn();
  }

  // Show all dimension descriptions
  ImGui::Separator(); 
  ImGui::Checkbox("Technical names", &showTechnicalNames);
  ImGui::NextColumn();
  ImGui::Text("Vertex"); ImGui::NextColumn();
  ImGui::Text("Edge"); ImGui::NextColumn();
  ImGui::Text("Face"); ImGui::NextColumn();
  ImGui::Text("Cell"); ImGui::NextColumn();
  ImGui::Text("4-face"); ImGui::NextColumn();

  // Point
  ImGui::Separator(); 
  if (ImGui::Button(!showTechnicalNames ? "Point" : "Monon")) {
    scaleTarget = glm::vec4(0.f, 0.f, 0.f, 0.f);
  }
  ImGui::NextColumn();
  ImGui::Text("1"); ImGui::NextColumn();
  for (unsigned int i = 0; i < 6 - 2; ++i) {
    ImGui::NextColumn();
  }

  // Line Segment
  ImGui::Separator(); 
  if (ImGui::Button(!showTechnicalNames ? "Line Segment" : "Dion")) {
    scaleTarget = glm::vec4(1.f, 0.f, 0.f, 0.f);
  }
  ImGui::NextColumn();
  ImGui::Text("2"); ImGui::NextColumn();
  ImGui::Text("1"); ImGui::NextColumn();
  for (unsigned int i = 0; i < 6 - 3; ++i) {
    ImGui::NextColumn();
  }

  // Square
  ImGui::Separator(); 
  if (ImGui::Button(!showTechnicalNames ? "Square" : "Tetragon")) {
    scaleTarget = glm::vec4(1.f, 1.f, 0.f, 0.f);
  }
  ImGui::NextColumn();
  ImGui::Text("4"); ImGui::NextColumn();
  ImGui::Text("4"); ImGui::NextColumn();
  ImGui::Text("1"); ImGui::NextColumn();
  for (unsigned int i = 0; i < 6 - 4; ++i) {
    ImGui::NextColumn();
  }

  // Cube
  ImGui::Separator(); 
  if (ImGui::Button(!showTechnicalNames ? "Cube" : "Hexahedron")) {
    scaleTarget = glm::vec4(1.f, 1.f, 1.f, 0.f);
  }
  ImGui::NextColumn();
  ImGui::Text("8"); ImGui::NextColumn();
  ImGui::Text("12"); ImGui::NextColumn();
  ImGui::Text("6"); ImGui::NextColumn();
  ImGui::Text("1"); ImGui::NextColumn();
  for (unsigned int i = 0; i < 6 - 5; ++i) {
    ImGui::NextColumn();
  }

  // Tesseract
  ImGui::Separator(); 
  if (ImGui::Button(!showTechnicalNames ? "Tesseract" : "Octachoron")) {
    scaleTarget = glm::vec4(1.f, 1.f, 1.f, 1.f);
  }
  ImGui::NextColumn();
  ImGui::Text("16"); ImGui::NextColumn();
  ImGui::Text("32"); ImGui::NextColumn();
  ImGui::Text("24"); ImGui::NextColumn();
  ImGui::Text("8"); ImGui::NextColumn();
  ImGui::Text("1"); ImGui::NextColumn();

  // Final seperator at end of table
  ImGui::Columns(1);
  ImGui::Separator();
}
