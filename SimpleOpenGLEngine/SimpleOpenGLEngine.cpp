#include<iostream>
#include<string>

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Shader.h"
#include"stb_image.h"

//Prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);

/*
float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
*/

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(2.0f, 5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f, 3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f, 2.0f, -2.5f),
	glm::vec3(1.5f, 0.2f, -1.5f),
	glm::vec3(-1.3f, 1.0f, -1.5f)
};

glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

float camYaw = -90.0f;
float camPitch = 0.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float fov = 45.0f;

double lastX = 0.0;
double lastY = 0.0;
bool firstMouse = true;

int main()
{
	//------------OpenGL Init-------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World!", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW Window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);

	//-----------Finished OpenGL Init--------------

	float vertices[] =
	{
		 0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f,   0.0f, 1.0f,

		 0.5f,  0.5f, 0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f, //these uvs cause interesting shearing due to converting them from GLDrawArrays
		 0.5f, -0.5f, 0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f, 0.5f,    1.0f, 0.0f, 1.0f,   1.0f, 0.0f
	};

	unsigned int indices[] =
	{
		0, 1, 3, //front
		1, 2, 3,

		5, 1, 0, //right 
		0, 4, 5,
	
		0, 3, 7, //top
		7, 4, 0,

		3, 2, 6, //left
		7, 3, 6,

		2, 1, 5, //bottom
		6, 2, 5,

		7, 6, 5, //back
		4, 7, 5
	};

	Shader basicShader("main.vert", "main.frag");

	//texture data
	stbi_set_flip_vertically_on_load(true);

	unsigned int texture;
	glGenTextures(1, &texture);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("uv2.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "ERROR: Failed to load image" << std::endl;
	}
	stbi_image_free(data);

	//vertex data
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	//Transformations
	//glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 model(1);
	model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 cam = glm::lookAt(camPos, camPos + camFront, camUp);

	//vec = cam * vec;
	//std::cout << vec.x << vec.y << vec.z << std::endl;

	glm::mat4 proj = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 100.0f);


	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		//Input
		processInput(window);

		cam = glm::lookAt(camPos, camPos + camFront, camUp);
		glm::mat4 proj = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.01f, 100.0f);

		//render
		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		basicShader.use();
		basicShader.setInt("ourTexture1", 0);

		glUniformMatrix4fv(glGetUniformLocation(basicShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(basicShader.ID, "cam"), 1, GL_FALSE, glm::value_ptr(cam));
		glUniformMatrix4fv(glGetUniformLocation(basicShader.ID, "proj"), 1, GL_FALSE, glm::value_ptr(proj));
		//glUniform1i(glGetUniformLocation(basicShader.ID, "ourTexture1"), 0);
		//glUniform1i(glGetUniformLocation(basicShader.ID, "ourTexture2"), 1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 tempModel(1);
			tempModel = glm::translate(tempModel, cubePositions[i]);
			float angle = 20.0f * i;
			tempModel = glm::rotate(tempModel, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(glGetUniformLocation(basicShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(tempModel));
			//glDrawArrays(GL_TRIANGLES, 0, 36);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}
		glBindVertexArray(0);

		/*
		glBindVertexArray(VAO);
		//
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		*/

		//check events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	float currentframe = glfwGetTime();
	deltaTime = currentframe - lastFrame;
	lastFrame = currentframe;

	float camSpeed = 1.0f;
	float camRotationSpeed = 90.0f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camPos += camSpeed * camFront * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camPos -= camSpeed * camFront * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camPos -= glm::normalize(glm::cross(camFront, camUp)) * camSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camPos += glm::normalize(glm::cross(camFront, camUp)) * camSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camPos += camSpeed * camUp * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camPos -= camSpeed * camUp * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		camYaw -= camRotationSpeed * camSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		camYaw += camRotationSpeed * camSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		camPitch += camRotationSpeed * camSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		camPitch -= camRotationSpeed * camSpeed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		fov /= 1.01f;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		fov *= 1.01f;

	if (fov > 179.0f)
		fov = 179.0f;

	camFront.x = cos(glm::radians(camPitch)) * cos(glm::radians(camYaw));
	camFront.y = sin(glm::radians(camPitch));
	camFront.z = cos(glm::radians(camPitch)) * sin(glm::radians(camYaw));

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float sens = 0.05f;

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	xoffset *= sens;
	yoffset *= sens;

	camPitch += yoffset;
	camYaw += xoffset;

	camFront.x = cos(glm::radians(camPitch)) * cos(glm::radians(camYaw));
	camFront.y = sin(glm::radians(camPitch));
	camFront.z = cos(glm::radians(camPitch)) * sin(glm::radians(camYaw));
}