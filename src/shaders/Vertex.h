// Vertex.h
// Header-only file with hard-coded vertex shader code

#ifndef SHADERS_VERTEX_H
#define SHADERS_VERTEX_H

namespace App::Shaders {

  // Vertex shader source code
  const char* const vertexSource = "#version 330 core\n"
      "layout (location = 0) in vec4 aPos;\n"
      "uniform float transform[25];\n"
      "uniform float view4D[25];\n"
      "uniform float projTo3D[25];\n"
      "uniform mat4 view3D;\n"
      "uniform mat4 projTo2D;\n"
      "\n"
      "void mult(out float ret[5], in float a[25], in float b[5]) {\n"
      "   ret = float[5](0, 0, 0, 0, 0);\n"
      "   for (int j = 0; j < 5; j++) {\n"
      "     for (int i = 0; i < 5; i++) {\n"
      "         ret[j] += a[i + (j * 5)] * b[j];\n"
      "     }\n"
      "   }\n"
      "}\n"
      "\n"
      "void main() {\n"
      "   float pos[5] = float[5](aPos.x, aPos.y, aPos.z, aPos.w, 1);\n"
      "   mult(pos, transform, pos);\n"
      "   mult(pos, view4D, pos);\n"
      "   mult(pos, projTo3D, pos);\n"
      "   vec4 p = vec4(pos[0], pos[1], pos[2], pos[3]) / 1;\n"
      "   gl_Position = (projTo2D * view3D * p) / p.w;\n"
      "}\0";
}

#endif
