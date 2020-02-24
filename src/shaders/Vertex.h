// Vertex.h
// Header-only file with hard-coded vertex shader code

#ifndef SHADERS_VERTEX_H
#define SHADERS_VERTEX_H

namespace App::Shaders {

  // Vertex shader source code
  const char* const vertexSource = "#version 330 core\n"
      "layout (location = 0) in vec4 aPos;\n"
      "uniform mat4 transform;\n"
      "uniform mat4 view;\n"
      "uniform mat4 projection;\n"
      "void main()\n"
      "{\n"
      "   vec4 pos = vec4(aPos.xyz, 1);\n"
      "   gl_Position = projection * view * transform * pos;\n"
      "}\0";
}

#endif
