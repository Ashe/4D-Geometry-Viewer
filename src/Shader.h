// Shader.h
// Class for compiling and storing a shader

#ifndef SHADER_H
#define SHADER_H

#include <cstdio>
#include <glad/glad.h>
#include <glm/ext.hpp>

namespace App {

  // Load shaders from files and / or strings
  class Shader {

    public:

      // Constructor
      Shader();

      // Prevent triggering destructors from moving
      // Use std::unique_ptr if movement is required
      Shader(const Shader&) = delete;

      // Ensure shaders are released
      ~Shader();

      // Get the ID of this shader
      unsigned int id() const;

      // Get whether this shader is ready to use
      bool getIsLoaded() const;

      // Set shader uniforms
      void setInt(const char* label, int value);
      void setFloat(const char* label, float value);
      void setFloat2(const char* label, const glm::vec2& fs);
      void setFloat3(const char* label, const glm::vec3& fs);
      void setFloat4(const char* label, const glm::vec4& fs);
      void setFloats(const char* label, unsigned int count, float* fs);
      void setMat4(const char* label, const glm::mat4& value);

      // Compile a shader using strings
      static bool compile(Shader& shader,
          const char* vertexSource, const char* fragmentSource);

    private:

      // ID for this shader
      unsigned int shaderProgramID;

      // Is this shader compiled and ready to use?
      bool isLoaded = false;

      // Compile shader code and return error code
      static bool compileShaderCode(unsigned int id, const char* source);

      // Display error information about shader
      static bool shaderErrorCheck(unsigned int id);
      static bool programErrorCheck(unsigned int id);
  };
}

#endif
