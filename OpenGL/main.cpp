

#if 1

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include<cmath>
#include<math.h>
#include<algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// my headers 
#include "core/Window.h"
#include "core/Shader.h"
#include "core/VertexArray.h"
#include "core/VertexBuffer.h"
#include "core/VertexBufferLayout.h"
#include "core/IndexBuffer.h"
#include "core/Renderer.h"
#include "core/Texture.h"

int main()
{
	using namespace core;

	std::string name = "Hello OpenGL";
	int width = 800;
	int height = 600;
	{
		Window mywindow(name.c_str(), width, height);

		// data
		float vertices[] = {
			// positions          // colors           // texture coords
			0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // top right
			0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,    1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
		};

		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		glm::vec4 color(0.2f, 0.3f, 0.3f, 1.0f);
		mywindow.setClearColor(color);

		VertexArray va;
		VertexBuffer vb(vertices, sizeof(vertices));
		IndexBuffer ib(indices, sizeof(indices));
		VertexBufferLayout layout;
		layout.Push<float>(3); // position 
		layout.Push<float>(3); // color
		layout.Push<float>(2); // texture
		va.AddBuffer(vb, layout);
		Shader shader("shaders/vertex.shader", "shaders/frag.shader");
		Renderer rend;

		float timeValue;

		// Texture 

		float visible = 0.4f;

		shader.SetUniform1f("vis", visible);
		shader.SetUniform1i("texture1", 1);
		shader.SetUniform1i("texture2", 2);

		Texture texture1("textures/container.jpg");
		Texture texture2("textures/awesomeface.png");

		texture1.Bind(1); 
		texture2.Bind(2);


		// drawing loop 
		while (mywindow.closed() == 0)
		{
			mywindow.clear();

			if (mywindow.isKeyPressed(GLFW_KEY_ESCAPE) == 1) mywindow.close();
			else if (mywindow.isKeyPressed(GLFW_KEY_UP) == 1) visible += 0.001f;
			else if (mywindow.isKeyPressed(GLFW_KEY_DOWN) == 1) visible -= 0.001f;
			
			visible = std::max(0.0f, visible);
			visible = std::min(1.0f, visible);

			timeValue = (float)glfwGetTime();


			glm::mat4 trans;
			int scal = (int)(timeValue * 100) % 100;
			float fscal = scal / 100.0f;
			std::cout << scal << std::endl;
			trans = glm::rotate(trans, timeValue, glm::vec3(1.0f, 1.0f, 1.0f));
			trans = glm::scale(trans, glm::vec3(2.0, 2.0, 2.0f));

			shader.SetUniformMatrix4fv("transform", trans);
			shader.SetUniform1f("vis", visible);
			rend.Draw(va, ib, shader);

			mywindow.update();
		}
	}
	
	return 0;
}

#endif 