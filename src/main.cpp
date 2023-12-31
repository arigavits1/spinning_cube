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
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
unsigned int WIDTH = 1920;
unsigned int HEIGHT = 1080;

bool draw = true;
bool polygonMode = false;
float textureMergeAmount = 0.2f;

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int WIDTH, int HEIGHT);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

int main()
{
	WinData windowData;
	Window window(WIDTH, HEIGHT, "Game Engine v1.2", false);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.MouseDrawCursor = false;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");

	Shader shader("../resources/object.shader");

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

	unsigned int indices[] = {
		0, 1, 2,   // Front face
		3, 4, 5,   // Back face
		6, 7, 8,   // Left face
		9, 10, 11, // Right face
		12, 13, 14,   // Top face
		15, 16, 17,   // Bottom face
		18, 19, 20,   // Front face
		21, 22, 23,   // Back face
		24, 25, 26,   // Left face
		27, 28, 29, // Right face
		30, 31, 32,   // Top face
		33, 34, 35   // Bottom face
	};

	Texture texture1(GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGB, GL_RGB, "../resources/textures/container.jpg", false, GL_TEXTURE0);
	Texture texture2(GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST, GL_RGBA, GL_RGBA, "../resources/textures/awesomeface.png", true, GL_TEXTURE1);

	VBO cubeVBO(GL_ARRAY_BUFFER, sizeof(vertices), vertices);

	VAO cubeVAO;
	cubeVAO.CreateAttribArray(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)0);
	cubeVAO.CreateAttribArray(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(3 * sizeof(float)));

	EBO cubeEBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	float prevTime = 0.0f;
	float currentTime = 0.0f;

	shader.use();
	glUniform1i(glGetUniformLocation(shader.program, "texture1"), 1);
	glUniform1i(glGetUniformLocation(shader.program, "texture2"), 0);

	glm::vec3 scale = glm::vec3(1.0f);
	glm::vec3 color = glm::vec3(1.0f);
	float scaleAmount = 1.0f;
	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		
		glfwSetWindowUserPointer(window.GetWindow(), &windowData);
		currentTime = (float)glfwGetTime();
		windowData.deltaTime = currentTime - prevTime;
		prevTime = currentTime;

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		texture1.activate();
		texture2.activate();

		glUniform3f(glGetUniformLocation(shader.program, "color"), color.x, color.y, color.z);
		glUniform1f(glGetUniformLocation(shader.program, "textureMergeAmountUniform"), textureMergeAmount);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.3f, 0.0f));
		model = glm::rotate(model, glm::radians((float)glfwGetTime() * 100.0f + 45.0f * windowData.deltaTime), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, scale);
		int modelLoc = glGetUniformLocation(shader.program, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::lookAt(windowData.cameraPos, windowData.cameraPos + windowData.cameraFront, windowData.cameraUp);
		int viewLoc = glGetUniformLocation(shader.program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 50.0f);
		int projectionLoc = glGetUniformLocation(shader.program, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		shader.use();

		if (draw)
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		ImGui::SetNextWindowSize(ImVec2(200, WIDTH));
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::Begin("Properties Window");
		if (ImGui::Button("Close window"))
		{
			glfwSetWindowShouldClose(window.GetWindow(), true);
		}
		ImGui::Checkbox("Draw sqaure", &draw);
		ImGui::Checkbox("Polygon Mode", &polygonMode);
		ImGui::SliderFloat("Scale", &scaleAmount, -2.0f, 2.0f);
		ImGui::SliderFloat("Texture Merge", &textureMergeAmount, 0.0f, 1.0f);
		ImGui::ColorEdit3("Color", glm::value_ptr(color));
		scale.x = scaleAmount;
		scale.y = scaleAmount;
		scale.z = scaleAmount;
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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