#pragma once


#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) core::ErrorHandler::GLClearError();\
	x;\
	ASSERT(core::ErrorHandler::GLLogCall(#x, __FILE__, __LINE__))

namespace core
{
	class ErrorHandler
	{
	public:
		static bool GLLogCall(const char* function, const char* file, int line);
		static void GLClearError();
	};
}