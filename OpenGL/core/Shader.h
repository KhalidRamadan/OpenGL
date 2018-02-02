#pragma once


#include<string>
#include<unordered_map>
#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../math/vec4.h"

namespace core
{

	class Shader
	{
	private:
		unsigned int m_RendererID;
		std::unordered_map<std::string, int> Cache;
	public:
		Shader(const std::string& vertexpath, const std::string& fragmentpath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		// Set Uniforms
		void SetUniform4f(const std::string& name, math::vec4 value);
		void SetUniform1f(const std::string& name, float value);
	private:
		int GetUniformLocation(const std::string& name);
		std::string read_file(const char* filepath);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		unsigned int CompileShader(unsigned int type, const std::string& source);
	};

}