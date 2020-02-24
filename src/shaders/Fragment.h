// Fragment.h
// Header only file with hard-coded fragment shader code

#ifndef SHADERS_FRAGMENT_H
#define SHADERS_FRAGMENT_H

namespace App::Shaders {

  // Fragment shader source code
  const char* const fragmentSource = "#version 330 core\n"
      "out vec4 FragColor;\n"
      "void main()\n"
      "{\n"
      "   FragColor = vec4(1, 1, 1, 1);\n"
      "}\0";
}

#endif
