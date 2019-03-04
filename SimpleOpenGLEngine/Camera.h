#pragma once

#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

class Camera
{
public:
	Camera(glm::vec3 pos);

	void processGLFWInput(GLFWwindow* window, float deltaTime); //this shuld be temporary
	void mouseCallBack(GLFWwindow* window, double xpos, double ypos);

	void addYaw(float amount);
	void addPitch(float amount);

	void setFOV(float amount);
	float getFOV() const;

	glm::mat4 getCameraTransform() const;

private:
	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Up;

	float pitch;
	float yaw;
	float fov;

	float speed;
	float rotationSpeed;

	void recalculate();
};