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
      }
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
    }
  }

  // Push generated vertices to these buffers
  updateVertices(GL_LINES, vertexCount, indexCount);
}

// Show information about the hyperoctahedron
void 
App::Hyperoctahedron::showPolytopeInfo() {

  // Prepare to show types of hypercubes
  static bool showTechnicalNames = false;

  // Show table of hyperoctahedrons
  ImGui::Columns(6, NULL, true);
  ImGui::SetColumnWidth(0, 155.0f);
  ImGui::Separator();
  ImGui::Text("Hyperoctahedron");
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
  if (ImGui::Button(!showTechnicalNames ? "Line Segment" : "1-orthoplex")) {
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
  if (ImGui::Button(!showTechnicalNames ? "Square" : "Bicross")) {
    scaleTarget = glm::vec4(1.f, 1.f, 0.f, 0.f);
  }
  ImGui::NextColumn();
  ImGui::Text("4"); ImGui::NextColumn();
  ImGui::Text("4"); ImGui::NextColumn();
  ImGui::Text("1"); ImGui::NextColumn();
  for (unsigned int i = 0; i < 6 - 4; ++i) {
    ImGui::NextColumn();
  }

  // Tricross
  ImGui::Separator(); 
  if (ImGui::Button(!showTechnicalNames ? "Tricross" : "Octahedron")) {
    scaleTarget = glm::vec4(1.f, 1.f, 1.f, 0.f);
  }
  ImGui::NextColumn();
  ImGui::Text("6"); ImGui::NextColumn();
  ImGui::Text("12"); ImGui::NextColumn();
  ImGui::Text("8"); ImGui::NextColumn();
  ImGui::Text("1"); ImGui::NextColumn();
  for (unsigned int i = 0; i < 6 - 5; ++i) {
    ImGui::NextColumn();
  }

  // Tetracross
  ImGui::Separator(); 
  if (ImGui::Button(!showTechnicalNames ? "Tetracross" : "Hexadecachoron")) {
    scaleTarget = glm::vec4(1.f, 1.f, 1.f, 1.f);
  }
  ImGui::NextColumn();
  ImGui::Text("8"); ImGui::NextColumn();
  ImGui::Text("24"); ImGui::NextColumn();
  ImGui::Text("32"); ImGui::NextColumn();
  ImGui::Text("16"); ImGui::NextColumn();
  ImGui::Text("1"); ImGui::NextColumn();

  // Final seperator at end of table
  ImGui::Columns(1);
  ImGui::Separator();

}
