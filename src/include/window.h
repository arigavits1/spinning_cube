#pragma once
#include <GLFW/glfw3.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "WindowData.h"

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int WIDTH, int HEIGHT);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

class Window
{
public:
    Window(unsigned int WIDTH, unsigned int HEIGHT, const char* title, bool fullScreen);
    GLFWwindow* GetWindow();

private:
    float lastX = 0.0f;
    float lastY = 0.0f;
    GLFWwindow* window;
};