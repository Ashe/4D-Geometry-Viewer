// Shader.cpp
// Class for compiling and storing a shader

#include "Shader.h"

// Constructor
App::Shader::Shader() {
  shaderProgramID = glCreateProgram();
  isLoaded = false;
}

// Destructor
App::Shader::~Shader() {
  glDeleteProgram(shaderProgramID);
}

// Compile a shader using strings
bool 
App::Shader::compile(Shader& shader,
    const char* vertexSource, const char* fragmentSource) {

  // Prepare to compile all shader data
  bool success = true;

  // Compile the vertex shader
  const unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
  success &= Shader::compileShaderCode(vertex, vertexSource);

  // Compile fragment shader
  const unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);
  success &= Shader::compileShaderCode(frag, fragmentSource);

  // If there's errors, exit now
  if (!success) {
    printf("[Error] Compilation failed. Shader program won't be linked.\n");
    return false;
  }

  // Link shader program
  glAttachShader(shader.id(), vertex);
  glAttachShader(shader.id(), frag);
  glLinkProgram(shader.id());
  success = Shader::programErrorCheck(shader.id());

  // Delete shader objects
  glDeleteShader(vertex);
  glDeleteShader(frag);

  // Return the result of the last check
  shader.isLoaded = success;
  return success;
}

// Set shader uniforms
void App::Shader::setInt(const char* label, int i) {
  glUniform1i(glGetUniformLocation(id(), label), i);
}
void App::Shader::setFloat(const char* label, float f) {
  glUniform1f(glGetUniformLocation(id(), label), f);
}
void App::Shader::setFloat2(const char* label, const glm::vec2& fs) {
  glUniform2f(glGetUniformLocation(id(), label), fs.x, fs.y);
}
void App::Shader::setFloat3(const char* label, const glm::vec3& fs) {
  glUniform3f(glGetUniformLocation(id(), label), fs.x, fs.y, fs.z);
}
void App::Shader::setFloat4(const char* label, const glm::vec4& fs) {
  glUniform4f(glGetUniformLocation(id(), label), fs.x, fs.y, fs.z, fs.w);
}
void 
App::Shader::setFloats(const char* label, unsigned int count, float* fs) {
    glUniform1fv(glGetUniformLocation(id(), label), sizeof(float) * count, fs);
}
void 
App::Shader::setMat4(const char* label, const glm::mat4& m) {
  glUniformMatrix4fv(glGetUniformLocation(id(), label), 
      1, GL_FALSE, glm::value_ptr(m));
}

// Compile shader code and return error code
bool 
App::Shader::compileShaderCode(unsigned int id, const char* source) {
  glShaderSource(id, 1, &source, NULL);
  glCompileShader(id);
  return Shader::shaderErrorCheck(id);
}

// Display error information about shader
bool 
App::Shader::shaderErrorCheck(unsigned int id) {
  int success;
  char info[512];
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(id, 512, NULL, info);
    printf("[Error] Failed to compile shader for program: %u.\n", id);
    printf("%s\n", info);
    return false;
  }
  return true;
}

// Display error information about program
bool 
App::Shader::programErrorCheck(unsigned int id) {
  int success;
  char info[512];
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if(!success) {
    glGetProgramInfoLog(id, 512, NULL, info);
    printf("[Error] Failed to link shader program: %u.\n", id);
    printf("%s\n", info);
    return false;
  }
  return true;
}

// Get the ID of this shader
unsigned int
App::Shader::id() const {
  return shaderProgramID;
}

// Get whether this shader is ready to use
bool
App::Shader::getIsLoaded() const {
  return isLoaded;
}
