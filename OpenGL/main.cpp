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
#include "core/graphics.hpp"
#include "game/Camera.hpp"
#include "data.hpp"



int main()
{

	std::string name = "Hello OpenGL";
	int width = 800;
	int height = 600;
	{
		core::Window mywindow(name.c_str(), width, height);
		core::VertexArray va;
		core::VertexBuffer vb(vertices, sizeof(vertices));
		core::IndexBuffer ib(indices, sizeof(indices));
		core::VertexBufferLayout layout;
		core::Shader shader("shaders/vertex.shader", "shaders/frag.shader");
		core::Renderer rend;

		glm::vec4 color(0.2f, 0.3f, 0.3f, 1.0f);
		mywindow.SetClearColor(color);
		layout.Push<float>(3); // position 
		//layout.Push<float>(3); // color
		layout.Push<float>(2); // texture
		va.AddBuffer(vb, layout);


		// Texture 
		core::Texture t1("textures/container.jpg");
		core::Texture t2("textures/Small-mario.png");

		shader.SetUniform1i("texture1", 0);
		shader.SetUniform1i("texture2", 1);

		t1.Bind(0);
		t2.Bind(1);

		shader.SetUniform1f("vis", 0.4f);

		mywindow.EnableDepthTest();
		mywindow.DisableCursore();

		game::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

		mywindow.SetCamera(camera);


		glm::mat4 model; glm::mat4 projection; glm::mat4 view;

		// drawing loop 

		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
		while (!mywindow.Closed())
		{
			mywindow.Clear();


			projection = glm::perspective(glm::radians(camera.Zoom), (float)(width / height), 0.1f, 100.0f);

			view = camera.GetViewMatrix();

			for (int i = 0; i < 10; i++)
			{
				float angle = 50.0f;
				angle = ((float)glfwGetTime() * angle);
				model = glm::translate(glm::mat4(), cubePositions[i]);
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				shader.SetUniformMatrix4fv("model", model);
				shader.SetUniformMatrix4fv("projection", projection);
				shader.SetUniformMatrix4fv("view", view);
				rend.DrawArrays(va, vb, layout, shader);
			}
			mywindow.Update();
		}
	}


	
	return 0;
}

#endif