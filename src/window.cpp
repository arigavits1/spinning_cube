#include "include/window.h"

Window::Window(unsigned int WIDTH, unsigned int HEIGHT, const char* title, bool fullScreen)
{
    if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        glfwTerminate();
        exit(1);
	}

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);

	WIDTH = videoMode->width;
	HEIGHT = videoMode->height;

	lastX = (float)WIDTH / 2;
	lastY = (float)HEIGHT / 2;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGHT, title, nullptr, nullptr);

	if (window == NULL)
	{
		std::cerr << "Failed to create window" << std::endl;
		ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        glfwTerminate();
        exit(1);
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSwapInterval(1);
}

GLFWwindow* Window::GetWindow()
{
    return window;
}

bool isEscapeReleased = true;
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
	{
		isEscapeReleased = true;
	}

	WinData* windowData = static_cast<WinData*>(glfwGetWindowUserPointer(window));
	if (isEscapeReleased && glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		isEscapeReleased = false;

		windowData->uiMode = !windowData->uiMode;
		windowData->firstMouse = true;
	}
	float cameraSpeed = 2.5f * windowData->deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		windowData->cameraPos -= cameraSpeed * glm::normalize(glm::cross(glm::normalize(glm::cross(windowData->cameraFront, windowData->cameraUp)), glm::vec3(0.0f, 1.0f, 0.0f)));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		windowData->cameraPos += cameraSpeed * glm::normalize(glm::cross(glm::normalize(glm::cross(windowData->cameraFront, windowData->cameraUp)), glm::vec3(0.0f, 1.0f, 0.0f)));
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		windowData->cameraPos -= cameraSpeed * glm::normalize(glm::cross(windowData->cameraFront, windowData->cameraUp));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		windowData->cameraPos += cameraSpeed * glm::normalize(glm::cross(windowData->cameraFront, windowData->cameraUp));
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		windowData->cameraPos -= cameraSpeed * windowData->cameraUp;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		windowData->cameraPos += cameraSpeed * windowData->cameraUp;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	
	WinData* windowData = static_cast<WinData*>(glfwGetWindowUserPointer(window));
	if (!windowData->uiMode)
	{
		if (windowData->firstMouse)
		{
			windowData->lastX = xpos;
			windowData->lastY = ypos;
			windowData->firstMouse = false;
		}

		float xoffset = xpos - windowData->lastX;
		float yoffset = windowData->lastY - ypos;
		windowData->lastX = xpos;
		windowData->lastY = ypos;

		const float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		windowData->yaw += xoffset;
		windowData->pitch += yoffset;

		if (windowData->pitch > 89.0f)
			windowData->pitch = 89.0f;
		if (windowData->pitch < -89.0f)
			windowData->pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(windowData->yaw)) * cos(glm::radians(windowData->pitch));
		direction.y = sin(glm::radians(windowData->pitch));
		direction.z = sin(glm::radians(windowData->yaw)) * cos(glm::radians(windowData->pitch));
		windowData->cameraFront = glm::normalize(direction);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int WIDTH, int HEIGTH)
{
	glViewport(0, 0, WIDTH, HEIGTH);
}