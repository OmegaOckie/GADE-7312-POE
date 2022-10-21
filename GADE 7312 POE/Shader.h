#pragma once

#include<iostream>
#include<fstream>
#include<string>

#include<glew.h>
#include<glfw3.h>

#include<glm.hpp>
#include<vec2.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat4x4.hpp>
#include<gtc/type_ptr.hpp>

class Shader
{
private:
	//Member Variables
	GLuint id;

	//Privat Functions
	std::string loadShaderSource(char* fileName)
	{
		std::string temp = "";
		std::string src = "";

		std::ifstream in_file;

		//Vertex
		in_file.open(fileName);

		if (in_file.is_open())
		{
			while (std::getline(in_file, temp))
			{
				src += temp + "\n";
			}
		}
		else
		{
			std::cout << "ERROR::LOADHSADERS::COULD_NOT_OPEN_FILE" << fileName << "\n";
		}
		in_file.close();

		return src;
	}
	
	GLuint loadShader(GLenum type, char* fileName)
	{
		char infoLog[512];
		GLint success;

		GLuint shader = glCreateShader(type);
		std::string str_src = this->loadShaderSource(fileName);
		const GLchar* src = str_src.c_str();
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COULD_NOT_COMPILE_SHADER" << fileName << "\n";
			std::cout << infoLog << "\n";
		}

		return shader;
	}

	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
	{
		char infoLog[512];
		GLint success;

		this->id = glCreateProgram();

		glAttachShader(this->id, vertexShader);

		if (geometryShader)
			glAttachShader(this->id, geometryShader);
		glAttachShader(this->id, geometryShader);

		glLinkProgram(this->id);

		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(this->id, 512, NULL, infoLog);
			std::cout << "ERROR::LOADHSADERS::COULD_NOT_LINK_PROGRAM" << "\n";
			std::cout << infoLog << "\n";
		}

		glUseProgram(0);
	}

public:

	//Constructor, Destructors
	Shader(char* vertexFile, char* fragmentFile, char* geometryFile)
	{
		GLuint vertexShader = 0;
		GLuint geometryShader = 0;
		GLuint fragmentShader = 0;

		vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);

		if (geometryFile != "")
			geometryShader = loadShader(GL_VERTEX_SHADER, geometryFile);
		fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

		this->linkProgram(vertexShader, geometryShader, fragmentShader);

		//END
		glDeleteShader(vertexShader);
		glDeleteShader(geometryShader);
		glDeleteShader(fragmentShader);
	}


	~Shader()
	{
		glDeleteProgram(this->id);
	}

};