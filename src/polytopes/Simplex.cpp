// Simplex.cpp
// A class storing a 5-cell polytope

#include "Simplex.h"

// Constructor
App::Simplex::Simplex() : Polytope() {

  // Precalculate values
  const float root3 = sqrt(3);
  const float root6 = sqrt(6);
  const float root10 = sqrt(10);

  // Generate vertices
  vertices = new float[5 * 4];
  unsigned int vertexCount = 0;

  vertices[vertexCount++] = 1.f / root10;
  vertices[vertexCount++] = 1.f / root6;
  vertices[vertexCount++] = 1.f / root3;
  vertices[vertexCount++] = - 1.f;

  vertices[vertexCount++] = 1.f / root10;
  vertices[vertexCount++] = 1.f / root6;
  vertices[vertexCount++] = 1.f / root3;
  vertices[vertexCount++] = 1.f;

  vertices[vertexCount++] = 1.f / root10;
  vertices[vertexCount++] = 1.f / root6;
  vertices[vertexCount++] = (- 2.f) / root3;
  vertices[vertexCount++] = 0.f;

  vertices[vertexCount++] = 1.f / root10;
  vertices[vertexCount++] = - sqrt(3.f / 2.f);
  vertices[vertexCount++] = 0.f;
  vertices[vertexCount++] = 0.f;

  vertices[vertexCount++] = (- 2.f) * sqrt(2.f / 5.f);
  vertices[vertexCount++] = 0.f;
  vertices[vertexCount++] = 0.f;
  vertices[vertexCount++] = 0.f;

  // Generate indices
  indices = new unsigned int[10 * 2];
  unsigned int indexCount = 0;

  indices[indexCount++] = 0;
  indices[indexCount++] = 1;
  indices[indexCount++] = 0;
  indices[indexCount++] = 2;
  indices[indexCount++] = 0;
  indices[indexCount++] = 3;
  indices[indexCount++] = 0;
  indices[indexCount++] = 4;

  indices[indexCount++] = 1;
  indices[indexCount++] = 2;
  indices[indexCount++] = 1;
  indices[indexCount++] = 3;
  indices[indexCount++] = 1;
  indices[indexCount++] = 4;

  indices[indexCount++] = 2;
  indices[indexCount++] = 3;
  indices[indexCount++] = 2;
  indices[indexCount++] = 4;

  indices[indexCount++] = 3;
  indices[indexCount++] = 4;

  // Push generated vertices to these buffers
  updateVertices(GL_LINES, vertexCount, indexCount);
}

// Show information about the simplex
void
App::Simplex::showPolytopeInfo() {

  // Prepare to show types of simplex
  static bool showTechnicalNames = false;

  // Show table of hypercubes
  ImGui::Columns(6, NULL, true);
  ImGui::SetColumnWidth(0, 155.0f);
  ImGui::Separator();
  ImGui::Text("Simplex");
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

  // Line segment
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

  // Triangle
  ImGui::Separator(); 
  if (ImGui::Button(!showTechnicalNames ? "Triangle" : "Trigon")) {
    scaleTarget = glm::vec4(1.f, 1.f, 0.f, 0.f);
  }
  ImGui::NextColumn();
  ImGui::Text("3"); ImGui::NextColumn();
  ImGui::Text("3"); ImGui::NextColumn();
  ImGui::Text("1"); ImGui::NextColumn();
  for (unsigned int i = 0; i < 6 - 4; ++i) {
    ImGui::NextColumn();
  }

  // Triangular Pyramid
  ImGui::Separator(); 
  if (ImGui::Button(!showTechnicalNames ? "Triangular Pyramid" : "Tetrahedron")) {
    scaleTarget = glm::vec4(1.f, 1.f, 1.f, 0.f);
  }
  ImGui::NextColumn();
  ImGui::Text("4"); ImGui::NextColumn();
  ImGui::Text("6"); ImGui::NextColumn();
  ImGui::Text("4"); ImGui::NextColumn();
  ImGui::Text("1"); ImGui::NextColumn();
  for (unsigned int i = 0; i < 6 - 5; ++i) {
    ImGui::NextColumn();
  }

  // Tetrahedral Pyramid
  ImGui::Separator(); 
  if (ImGui::Button(!showTechnicalNames ? "Tetrahedral Pyramid" : "Pentachoron")) {
    scaleTarget = glm::vec4(1.f, 1.f, 1.f, 1.f);
  }
  ImGui::NextColumn();
  ImGui::Text("5"); ImGui::NextColumn();
  ImGui::Text("10"); ImGui::NextColumn();
  ImGui::Text("10"); ImGui::NextColumn();
  ImGui::Text("5"); ImGui::NextColumn();
  ImGui::Text("1"); ImGui::NextColumn();

  // Final seperator at end of table
  ImGui::Columns(1);
  ImGui::Separator();
}
