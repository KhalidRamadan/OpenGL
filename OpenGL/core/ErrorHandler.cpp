#include "ErrorHandler.hpp"
#include <iostream>
#include <GL\glew.h>

namespace core
{

	void ErrorHandler::GLClearError()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	bool ErrorHandler::GLLogCall(const char* function, const char* file, int line)
	{
		while (GLenum error = glGetError())
		{
			std::cout << "[OpenGL Error] " << error << std::endl << "function Name : " << function
				<< std::endl << "File : " << file << std::endl << "Line : " << line << std::endl;
			return false;
		}
		return true;
	}
}
