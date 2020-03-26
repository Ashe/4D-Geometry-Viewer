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
      "uniform mat4 view3D;\n"
      "uniform mat4 projTo2D;\n"
      "\n"
      "void mult(out float ret[5], in float a[25], in float b[5]) {\n"
      "   float result[5] = float[5](0, 0, 0, 0, 0);\n"
      "   for (int j = 0; j < 5; j++) {\n"
      "     for (int i = 0; i < 5; i++) {\n"
      "         result[j] += a[j + (i * 5)] * b[i];\n"
      "     }\n"
      "   }\n"
      "   ret = float[5](0, 0, 0, 0, 0);\n"
      "   for (int i = 0; i < 5; i++) {\n"
      "       ret[i] = result[i];\n"
      "   }\n"
      "}\n"
      "\n"
      "void main() {\n"
      "   float pos[5] = float[5](aPos.x, aPos.y, aPos.z, aPos.w, 1);\n"
      "   mult(pos, transform, pos);\n"
      "   mult(pos, view4D, pos);\n"
      "   vec4 p = vec4(pos[0], pos[1], pos[2], pos[3]) / pos[4];\n"
      "   float d = 2.f;\n"
      "   mat3x4 to3D = mat3x4(\n"
      "       vec4(1 / (d - p.w), 0.f, 0.f, 0.f),\n"
      "       vec4(0.f, 1 / (d - p.w), 0.f, 0.f),\n"
      "       vec4(0.f, 0.f, 1 / (d - p.w), 0.f));\n"
      "   vec3 foo = p * to3D;\n"
      "   p = vec4(foo, 1);\n"
      "   gl_Position = (projTo2D * view3D * p) / p.w;\n"
      "}\0";
}

#endif
