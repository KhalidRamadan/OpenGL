#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

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
	{
		VertexArray va;

		VertexBuffer vb(position, 4 * 2 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		//  Index Buffer
		IndexBuffer ib(indices, 6);
		// End Index Buffer

		// shader 
		Shader shader("shaders/vertex.shader", "shaders/frag.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.3f, 0.2f, 0.3f, 1.0f);
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
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));



			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwTerminate();
	}
	return 0;
}