#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Camera.h"

Camera::Camera(glm::vec3 pos)
{
	Position = pos;
	Forward = glm::vec3(0.0f, 0.0f, -1.0f);
	Up = glm::vec3(0.0f, 1.0f, 0.0f);

	pitch = 0;
	yaw = 0;
	fov = 75;

	speed = 1.0f;
	rotationSpeed = 90.0f;

	recalculate();
}

void Camera::addYaw(float amount)
{
	yaw += amount;
	recalculate();
}

void Camera::addPitch(float amount)
{
	pitch += amount;
	recalculate();
}


void Camera::setFOV(float amount)
{
	fov = amount;
}

float Camera::getFOV() const
{
	return fov;
}

void Camera::processGLFWInput(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Position += speed * Forward * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Position -= speed * Forward * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Position -= glm::normalize(glm::cross(Forward, Up)) * speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Position += glm::normalize(glm::cross(Forward, Up)) * speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		Position += speed * Up * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		Position -= speed * Up * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		yaw -= rotationSpeed * speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		yaw += rotationSpeed * speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		pitch += rotationSpeed * speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		pitch -= rotationSpeed * speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		fov /= 1.01f;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		fov *= 1.01f;

	if (fov > 179.0f)
		fov = 179.0f;

	recalculate();
}

glm::mat4 Camera::getCameraTransform() const
{
	return glm::lookAt(Position, Position + Forward, Up);
}

void Camera::mouseCallBack(GLFWwindow* window, double xpos, double ypos)
{
	return;
}

void Camera::recalculate()
{
	Forward.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	Forward.y = sin(glm::radians(pitch));
	Forward.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
}




