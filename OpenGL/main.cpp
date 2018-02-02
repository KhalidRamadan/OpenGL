

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

		int nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

		// data
		
		float triangle1[] = {
			  // positons		    // color
			  0.0f, 0.0f, 0.0f,		1.0f, 0.0f, 0.0f, // origin
			  0.0f, 0.8f, 0.0f,		0.0f, 1.0f, 0.0f, // right top 
			  0.8f, 0.0f, 0.0f,		0.0f, 0.0f, 1.0f, // right down
		};

		float triangle2[] = {		
			// positons			    // color
			  0.0f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,	// origin
			  0.0f, 0.8f, 0.0f,		1.0f, 0.0f, 0.0f,	// left top 
			 -0.8f, 0.0f, 0.0f,		0.0f, 0.0f, 1.0f	// left down
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
		layout1.Push<float>(3);
		layout2.Push<float>(3);
		layout2.Push<float>(3);

		va1.AddBuffer(vb1, layout1);
		va2.AddBuffer(vb2, layout2);

		Shader shader1("shaders/vertex1.shader", "shaders/frag1.shader");
		Shader shader2("shaders/vertex2.shader", "shaders/frag2.shader");

		Renderer rend;



		float offset1 = 0.5f;
		float offset2 = 0.5f;
		float timeValue, greenValue, redValue;
		//lPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// Texture 

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);


		float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);





		while (mywindow.closed() == 0)
		{
			mywindow.clear();


			timeValue = glfwGetTime();
			offset1 = (sin(timeValue) / 2.0f);
			offset2 = (cos(timeValue) / 2.0f);
			std::cout << offset1 << " " << offset2 << std::endl;
			if (mywindow.isKeyPressed(GLFW_KEY_ESCAPE) == 1)
				mywindow.close();

			shader1.SetUniform1f("offset1", offset1);
			rend.Draw(va1, ib1, shader1);
			shader2.SetUniform1f("offset2", offset2);
			rend.Draw(va2, ib2, shader2);

			mywindow.update();
		}
	}
	

	//system("PAUSE");
	return 0;
}

#endif 