#include "include/UserInterface.h"

bool draw = true;
bool polygonMode = false;
float textureMergeAmount = 0.2f;
float scaleAmount = 1.0f;
glm::vec3 color = glm::vec3(1.0f);

UserInterface::UserInterface(GLFWwindow* p_window, unsigned int p_WinWidth, unsigned int p_WinHeight) : window(p_window), WinWidth(p_WinHeight), WinHeight(p_WinHeight)
{
    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.MouseDrawCursor = false;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void UserInterface::NewFrame()
{
    ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();
}

void UserInterface::Update()
{
    ImGui::SetNextWindowSize(ImVec2(200, WinWidth));
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::Begin("Properties Window");
	if (ImGui::Button("Close window"))
	{
		glfwSetWindowShouldClose(window, true);
	}
	ImGui::Checkbox("Draw sqaure", &draw);
	ImGui::Checkbox("Polygon Mode", &polygonMode);
	ImGui::SliderFloat("Scale", &scaleAmount, -2.0f, 2.0f);
	ImGui::SliderFloat("Texture Merge", &textureMergeAmount, 0.0f, 1.0f);
	ImGui::ColorEdit3("Color", glm::value_ptr(color));
	ImGui::End();
}

void UserInterface::Render()
{
    ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}