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

	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	unsigned int program;

	Shader(const char* filepath)
	{
		std::ifstream stream(filepath);
		std::string line;

		std::stringstream ss[2];
		int index;

		while (std::getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					index = 0;
					continue;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					index = 1;
					continue;
				}
			}

			ss[index] << line << "\n";
		}

		ShaderProgramSource source;
		source.VertexSource = ss[0].str();
		source.FragmentSource = ss[1].str();

		program = CreateShader(source.VertexSource, source.FragmentSource);
	}

	void use()
	{
		glUseProgram(program);
	}

private:

	unsigned int CompileShader(unsigned int type, std::string& source)
	{
		unsigned int shader = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);

		int result;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cerr << "ERROR COMPILING " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " SHADER\n" << infoLog << std::endl;
			return 0;
		}

		return shader;
	}

	unsigned int CreateShader(std::string& vertexSource, std::string& fragmentSource)
	{
		unsigned int program = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexSource);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);

		int result;
		glGetProgramiv(program, GL_LINK_STATUS, &result);

		if (!result)
		{
			char infoLog[512];
			glGetProgramInfoLog(program, 512, nullptr, infoLog);
			std::cerr << "FAILED TO LINK PROGRAM\n" << infoLog << std::endl;
		}

		return program;
	}
};