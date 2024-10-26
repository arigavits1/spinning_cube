#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

extern bool draw;
extern bool polygonMode;
extern float textureMergeAmount;
extern float scaleAmount;
extern glm::vec3 colorValues;

class UserInterface
{
public:
    UserInterface(GLFWwindow* p_window, unsigned int p_WinWidth, unsigned int p_WinHeight);
    void NewFrame();
    void Update();
    void Render();

private:
    GLFWwindow* window;
    unsigned int WinWidth;
    unsigned int WinHeight;
};