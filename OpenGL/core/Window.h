#pragma once
#include<iostream>
#include<string>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include "ErrorHandler.h"
#include <glm/glm.hpp>
#include "../game/Camera.h"


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
		double mx, my, fov; // X mouse position , Y mouse posistion , field of view 
	public:
		//todo
		//Window();
		Window(const char *title, int width, int height);
		~Window();
		void Update();
		bool Closed() const;
		void Clear() const;
		void Close() const;
		void EnableDepthTest() const;
		void DisableDepthTest() const;
		void EnableCursore() const;
		void DisableCursore() const;
		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

		// input 
		bool IsKeyPressed(unsigned int key) const;
		bool IsMouseButtonPressed(unsigned int button) const;
		void GetMousePosition(double &x, double &y) const;

		void SetClearColor(glm::vec4 color) const;

	private:
		bool Init();

		friend void window_resize(GLFWwindow *window, int width, int height);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		friend void scroll_position_callback(GLFWwindow* window, double xoffset, double yoffset);
		friend class game::Camera;
	};
}