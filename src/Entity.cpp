#include "include/Entity.h"

Entity::Entity(VAO p_vao, VBO p_vbo, EBO p_ebo, Shader p_shader, unsigned int p_WinWidth = 0, unsigned int p_WinHeight = 0, Texture* p_texture1 = NULL, Texture* p_texture2 = NULL) : vao(p_vao), vbo(p_vbo), ebo(p_ebo), texture1(*p_texture1), texture2(*p_texture2), shader(p_shader), WinWidth(p_WinWidth), WinHeight(p_WinHeight)
{    
    shader.use();
    vbo.use();
    vao.use();
    if (ebo != nullptr)
    {
        ebo.use();
    }
	glUniform1i(glGetUniformLocation(shader.program, "texture1"), 1);
	glUniform1i(glGetUniformLocation(shader.program, "texture2"), 0);
}

void Entity::update(WindowData windowData)
{
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
	projection = glm::perspective(glm::radians(45.0f), (float)WinWidth / (float)WinHeight, 0.1f, 50.0f);
	int projectionLoc = glGetUniformLocation(shader.program, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));		
	scale.x = scaleAmount;
	scale.y = scaleAmount;
	scale.z = scaleAmount;
}