#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <iostream>

#include "include/shaders.h"
#include "include/VAO.h"
#include "include/VBO.h"
#include "include/EBO.h"
#include "include/WindowData.h"
#include "include/window.h"
#include "include/texture.h"
#include "include/EntityData.h"
#include "include/UserInterface.h"
#include "include/Entity.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
unsigned int WIDTH = 1920;
unsigned int HEIGHT = 1080;

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int WIDTH, int HEIGHT);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

int main()
{
	WinData windowData;
	Window window(WIDTH, HEIGHT, "Game Engine v1.3", false);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	UserInterface UI(window.GetWindow(), WIDTH, HEIGHT);
	Shader shader("../resources/cube.shader");

	Texture texture1(GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGB, GL_RGB, "../resources/textures/container.jpg", false, GL_TEXTURE0);
	Texture texture2(GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST, GL_RGBA, GL_RGBA, "../resources/textures/awesomeface.png", true, GL_TEXTURE1);

	VBO cubeVBO(GL_ARRAY_BUFFER, sizeof(Cube::vertices), Cube::vertices);

	VAO cubeVAO;
	cubeVAO.CreateAttribArray(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)0);
	cubeVAO.CreateAttribArray(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(3 * sizeof(float)));

	EBO cubeEBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(Cube::indices), Cube::indices, GL_STATIC_DRAW);

	float prevTime = 0.0f;
	float currentTime = 0.0f;

	Entity Cube(cubeVAO, cubeVBO, cubeEBO, shader, WIDTH, HEIGHT, &texture1, &texture2);
	
	while (!glfwWindowShouldClose(window.GetWindow()))
	{		
		glfwSetWindowUserPointer(window.GetWindow(), &windowData);
		currentTime = (float)glfwGetTime();
		windowData.deltaTime = currentTime - prevTime;
		prevTime = currentTime;

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Cube.update(windowData);

		if (draw)
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

		UI.NewFrame();
		UI.Update();
		UI.Render();

		(windowData.uiMode ? glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL) : glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED));
		glPolygonMode(GL_FRONT_AND_BACK, (polygonMode ? GL_LINE : GL_FILL));
		processInput(window.GetWindow());

		glfwPollEvents();
		glfwSwapBuffers(window.GetWindow());
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	glfwTerminate();
	return 0;
}