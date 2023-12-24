#pragma once

#include <glm/glm.hpp>

struct WindowData
{
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	bool uiMode = true;
	bool firstMouse = true;
	float deltaTime = 0.0f;	
	float lastX, lastY;
	float yaw = -90.0f, pitch = 0.0f;
} typedef WinData;