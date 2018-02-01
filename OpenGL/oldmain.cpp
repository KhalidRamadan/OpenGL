
#if 0
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "core/Renderer.h"
#include "core/IndexBuffer.h"
#include "core/VertexBuffer.h"
#include "core/VertexBufferLayout.h"
#include "core/VertexArray.h"
#include "core/Shader.h"     

int main(void)
{
	GLFWwindow* window;
	if (!glfwInit()) return -1;
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if (glewInit() != GLEW_OK) std::cout << "ERROR" << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;

	float position[] = {
		-0.5f, -0.5f, // 0
		0.5f, -0.5f, // 1 
		0.5f,  0.5f, // 2
		-0.5f,  0.5f, // 3
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	// ==================================================================================
	VertexArray va;
	VertexBuffer vb(position, 4 * 2 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	IndexBuffer ib(indices, 6);
	Shader shader("shaders/vertex.shader", "shaders/frag.shader");
	shader.Bind();
	shader.SetUniform4f("u_Color", 0.3f, 0.2f, 0.3f, 1.0f);
	Renderer renderer;
	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();
		renderer.Draw(va, ib, shader);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
#endif
