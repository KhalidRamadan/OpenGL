

#if 1

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>


// my headers 
#include "core/Window.h"
#include "core/Shader.h"
#include "core/VertexArray.h"
#include "core/VertexBuffer.h"
#include "core/VertexBufferLayout.h"
#include "core/IndexBuffer.h"
#include "core/Renderer.h"


int main()
{
	using namespace core;
	using namespace math;
	std::string name = "Hello OpenGL";
	int width = 800;
	int height = 600;
	{
		Window mywindow(name.c_str(), width, height);


		// data
		float vertices[] = {
			0.5f,  0.5f, 0.0f,  // top right
			0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 

		};
		
		float triangle1[] = {
			0.0f, 0.0f, 0.0f, // origin
			0.5f, 0.5f, 0.0f, // right top 
			1.0f, 0.0f, 0.0f, // right down
		};

		float triangle2[] = {
			0.0f, 0.0f, 0.0f, // origin
			-0.5f, 1.0f, 0.0f, // left top 
			-1.0f, 0.0f, 0.0f // left down
		};


		unsigned int indices1[] = {  // note that we start from 0!
			0, 1, 2,   // first triangle
		};

		unsigned int indices2[] = {  // note that we start from 0!
			0, 1, 2   // second triangle
		};

		vec4 color(0.2f, 0.3f, 0.3f, 1.0f);

		mywindow.setClearColor(color);


		// first
		VertexArray va1;
		VertexArray va2;

		VertexBuffer vb1(triangle1, sizeof(triangle1));
		VertexBuffer vb2(triangle2, sizeof(triangle2));

		IndexBuffer ib1(indices1, sizeof(indices1));
		IndexBuffer ib2(indices2, sizeof(indices2));

		VertexBufferLayout layout1;
		VertexBufferLayout layout2;

		layout1.Push<float>(3);
		layout2.Push<float>(3);

		va1.AddBuffer(vb1, layout1);
		va2.AddBuffer(vb2, layout2);

		Shader shader1("shaders/vertex.shader", "shaders/frag1.shader");
		Shader shader2("shaders/vertex.shader", "shaders/frag2.shader");

		
		Renderer rend;
		while (mywindow.closed() == 0)
		{
			mywindow.clear();

			if (mywindow.isKeyPressed(GLFW_KEY_ESCAPE) == 1)
				mywindow.close();

			rend.Draw(va1, ib1, shader1);

			rend.Draw(va2, ib2, shader2);

			mywindow.update();
		}
	}
	

	system("PAUSE");
	return 0;
}

#endif 