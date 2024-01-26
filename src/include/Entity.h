#pragma once
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaders.h"
#include "texture.h"
#include "UserInterface.h"
#include "WindowData.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Entity
{
public:
    Entity(VAO p_vao, VBO p_vbo, EBO p_ebo, Shader p_shader, unsigned int p_WinWidth, unsigned int p_WinHeight, Texture* p_texture1, Texture* p_texture2);
    void update(WindowData windowData);

private:
    VAO vao;
    VBO vbo;
    EBO ebo;
    Texture texture1;
    Texture texture2;
    Shader shader;
    glm::vec3 scale = glm::vec3(1.0f);
	glm::vec3 color = glm::vec3(1.0f);
    unsigned int WinWidth;
    unsigned int WinHeight;
};