# CMakeList.txt : CMake project for SimpleOpenGLEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (SimpleOpenGLEngine	"SimpleOpenGLEngine.cpp" "SimpleOpenGLEngine.h"
									"Shader.cpp" "Shader.h"
									"stb_image.cpp" "stb_image.h"                  #TODO: Change the way this is presented so that the stb_image files do not look like source code
									"uv2.jpg" "main.vert" "main.frag") 

#resource files
configure_file("uv2.jpg" "${CMAKE_CURRENT_BINARY_DIR}/uv2.jpg" COPYONLY)			#TODO: this may not be the most elegent soulution for resourse files
configure_file("main.vert" "${CMAKE_CURRENT_BINARY_DIR}/main.vert" COPYONLY)
configure_file("main.frag" "${CMAKE_CURRENT_BINARY_DIR}/main.frag" COPYONLY)

# TODO: Add tests and install targets if needed.
#GLFW
target_link_libraries(${PROJECT_NAME} glfw)
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")

target_link_libraries(${PROJECT_NAME} glm)
target_include_directories(${PROJECT_NAME} PRIVATE "${GLM_DIR}/glm/include")

target_link_libraries(${PROJECT_NAME} glad)
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")