# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("SimpleOpenGLEngine")

# Include sub-projects.

#main project
add_subdirectory ("SimpleOpenGLEngine")

#GLFW
set(GLFW_DIR "glfw-3.2.1")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("${GLFW_DIR}")


#GLM
set(GLM_DIR "glm")
set(GLM_TEST_ENABLE OFF)
add_subdirectory("${GLM_DIR}")

#GLAD
set(GLAD_DIR "GLAD")
add_subdirectory("${GLAD_DIR}")



