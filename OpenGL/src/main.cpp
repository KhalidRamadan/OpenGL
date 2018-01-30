#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "Functions.h"

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"



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
	// Vertex Array 
	VertexArray va;

	VertexBuffer vb(position, 4 * 2 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	//  Index Buffer
	IndexBuffer ib(indices, 6);
	// End Index Buffer

	// shader 
	std::string vertexShader = engine::read_file("shaders/vertex.shader");
	std::string fragmentShader = engine::read_file("shaders/frag.shader");
	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);
	int location = glGetUniformLocation(shader, "u_Color");
	ASSERT(location != -1);
	float r = 0.0f;
	float inc = 0.01f;
	// end shader 

	// Unbind 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);


		// bind 

		//glBindBuffer(GL_ARRAY_BUFFER, buffer);
		ib.Bind();

		// draw
		if (r < 1.0f) r += inc; else r = 0.0f;
		glUniform4f(location, r, 0.5f, 0.3f, 1.0f);
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));


		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteShader(shader);
	glfwTerminate();
	return 0;
}