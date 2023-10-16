#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Shader
{
public:

	struct ShaderProgramSource;
	unsigned int program;
	Shader(const char* filepath);
	void use();

private:

	unsigned int CompileShader(unsigned int type, std::string& source);
	unsigned int CreateShader(std::string& vertexSource, std::string& fragmentSource);
};