#pragma once
#include<iostream>
#include<string>
#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include "ErrorHandler.h"
#include "../math/vec4.h"


#define MAX_KEYS 1024
#define MAX_BUTTONS 32
namespace core
{
	class Window
	{
	private:
		GLFWwindow* m_Window;
		const char *m_Title;
		int m_Width;
		int m_Height;
		bool m_Closed;
		bool m_Keys[MAX_KEYS];
		bool m_MouseButtons[MAX_BUTTONS];
		double mx, my;
	public:
		//todo
		//Window();
		Window(const char *title, int width, int height);
		~Window();
		void update();
		bool closed() const;
		void clear() const;
		void close() const;

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

		// input 
		bool isKeyPressed(unsigned int key) const;
		bool isMouseButtonPressed(unsigned int button) const;
		void getMousePosition(double &x, double &y) const;

		void setClearColor(math::vec4 color) const;

	private:
		bool init();

		friend void window_resize(GLFWwindow *window, int width, int height);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	};
}