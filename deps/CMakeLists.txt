# OpenGL
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
if (${OPENGL_FOUND})
  include_directories(${OPENGL_INCLUDE_DIR})
  link_libraries(${OPENGL_LIBRARIES})
endif()

# GLFW
set(GLFW_BUILD_EXAMPLES                 OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS                    OFF CACHE INTERNAL "")
set(GLFW_BUILD_DOCS                     OFF CACHE INTERNAL "")
set(GLFW_INSTALL                        OFF CACHE INTERNAL "")
add_subdirectory(glfw/)

# CPPLocate
set(cpplocate_DIR ${CMAKE_SOURCE_DIR}/deps/cpplocate/)
include(${CMAKE_SOURCE_DIR}/deps/cpplocate/cpplocate-config.cmake)
set(cpplocate_FOUND TRUE)

# GLBinding
set(BUILD_SHARED_LIBS                   ON  CACHE INTERNAL "")
set(OPTION_SELF_CONTAINED               OFF CACHE INTERNAL "")
set(OPTION_BUILD_TESTS                  OFF CACHE INTERNAL "")
set(OPTION_BUILD_DOCS                   OFF CACHE INTERNAL "")
set(OPTION_BUILD_TOOLS                  ON  CACHE INTERNAL "")
set(OPTION_BUILD_EXAMPLES               OFF CACHE INTERNAL "") 
set(OPTION_BUILD_WITH_BOOST_THREAD      OFF CACHE INTERNAL "")
set(OPTION_BUILD_CHECK                  OFF CACHE INTERNAL "")
add_subdirectory(glbinding/)

# GLAD
set(GLAD_ALL_EXTENSIONS                 ON  CACHE INTERNAL "")
set(GLAD_NO_LOADER                      OFF CACHE INTERNAL "")
set(GLAD_REPRODUCIBLE                   OFF CACHE INTERNAL "")
set(GLAD_EXPORT                         ON  CACHE INTERNAL "")
set(GLAD_INSTALL                        ON  CACHE INTERNAL "")
set(USE_MSVC_RUNTIME_LIBRARY_DLL        ON  CACHE INTERNAL "")
add_subdirectory(glad/)

# GLM
set(GLM_TEST_ENABLE                     OFF CACHE INTERNAL "")
set(BUILD_SHARED_LIBS                   OFF CACHE INTERNAL "")
set(BUILD_STATIC_LIBS                   OFF CACHE INTERNAL "")
add_subdirectory(glm/)

# Imgui
include(imgui.cmake)
