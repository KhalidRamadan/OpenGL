
#include "Window.h"


namespace core
{
	Window::Window(const char *title, int width, int height)
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;
		if (Init() == false)
			glfwTerminate();

		for (int i = 0; i < MAX_KEYS; i++)
		{
			m_Keys[i] = false;
		}

		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			m_MouseButtons[i] = false;
		}
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::Init()
	{
		if (!glfwInit())
		{
			std::cout << "Failed to Init GLFW" << std::endl;
			return false;
		}
		// change version of OpenGL , and make it core profile
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
		if (!m_Window)
		{
			glfwTerminate();
			std::cout << "Failed to create GLFW Window!!" << std::endl;
			return false;
		}


		glfwMakeContextCurrent(m_Window);
		// call back functions 
		glfwSetWindowUserPointer(m_Window, this);
		// glfwSetWindowSizeCallback
		glfwSetWindowSizeCallback(m_Window, window_resize);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Could not initizalize GLEW" << std::endl;
			return false;
		}
		return true;
	}

	void Window::SetClearColor(glm::vec4 color) const
	{
		glClearColor(color.x, color.y, color.z, color.w);
	}


	void Window::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void Window::Update()
	{

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}


	void Window::Close() const 
	{
		glfwSetWindowShouldClose(m_Window, true);
	}

	void Window::EnableDepthTest() const
	{
		glEnable(GL_DEPTH_TEST);
	}

	void Window::DisableDepthTest() const
	{
		glDisable(GL_DEPTH_TEST);
	}


	bool Window::Closed() const
	{
		return glfwWindowShouldClose(m_Window) == 1;
	}
	// input 

	bool Window::IsKeyPressed(unsigned int key) const
	{

		// todo:: Log input!
		if (key >= MAX_KEYS)
			return false;
		return m_Keys[key];
	}

	bool Window::IsMouseButtonPressed(unsigned int button) const
	{
		// todo:: Log input!
		if (button >= MAX_KEYS)
			return false;
		return m_MouseButtons[button];
	}

	void Window::GetMousePosition(double &x, double &y) const
	{
		x = mx;
		y = my;
	}



	// callback funtions 
	void window_resize(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window *win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window *win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MouseButtons[button] = action != GLFW_RELEASE;
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Window *win = (Window*)glfwGetWindowUserPointer(window);
		win->mx = xpos;
		win->my = ypos;
	}

}