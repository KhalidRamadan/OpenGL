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
#include "core/graphics.h"
#include "data.h"



using namespace core;

void KeyboardInput(const Window &window, glm::vec3 &cameraPos, const glm::vec3 &cameraFront,
	const glm::vec3 &cameraUp, float cameraSpeed)
{
	if (window.IsKeyPressed(GLFW_KEY_W)) cameraPos += cameraSpeed * cameraFront;
	else if (window.IsKeyPressed(GLFW_KEY_S)) cameraPos -= cameraSpeed * cameraFront;
	else if (window.IsKeyPressed(GLFW_KEY_A)) cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	else if (window.IsKeyPressed(GLFW_KEY_D)) cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}




int main()
{

	std::string name = "Hello OpenGL";
	int width = 800;
	int height = 600;
	{
		Window mywindow(name.c_str(), width, height);
		glm::vec4 color(0.2f, 0.3f, 0.3f, 1.0f);
		mywindow.SetClearColor(color);



		VertexArray va;
		VertexBuffer vb(vertices, sizeof(vertices));
		IndexBuffer ib(indices, sizeof(indices));
		VertexBufferLayout layout;
		layout.Push<float>(3); // position 
		//layout.Push<float>(3); // color
		layout.Push<float>(2); // texture
		va.AddBuffer(vb, layout);
		Shader shader("shaders/vertex.shader", "shaders/frag.shader");
		Renderer rend;

		float timeValue;

		// Texture 
		Texture t1("textures/container.jpg");
		Texture t2("textures/awesomeface.png");

		shader.SetUniform1i("texture1", 0);
		shader.SetUniform1i("texture2", 1);

		t1.Bind(0);
		t2.Bind(1);

		shader.SetUniform1f("vis", 0.4f);

		mywindow.EnableDepthTest();
		mywindow.DisableCursore();
		glm::vec3 cameraPos		= glm::vec3(0.0f, 0.0f,  6.0f);
		glm::vec3 cameraFront	= glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp		= glm::vec3(0.0f, 1.0f,  0.0f);


		glm::mat4 model;
		glm::mat4 projection;
		glm::mat4 view;

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		projection = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);


		shader.SetUniformMatrix4fv("model", model);
		shader.SetUniformMatrix4fv("projection", projection);
		shader.SetUniformMatrix4fv("view", view);

		float deltaTime = 0.0f;	// Time between current frame and last frame
		float lastFrame = 0.0f; // Time of last frame
		// drawing loop 
		while (!mywindow.Closed())
		{
			mywindow.Clear();

			if (mywindow.IsKeyPressed(GLFW_KEY_ESCAPE)) mywindow.Close();			
			if (mywindow.IsKeyPressed(GLFW_KEY_E)) mywindow.EnableCursore();
			if (mywindow.IsKeyPressed(GLFW_KEY_C)) mywindow.DisableCursore();
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			float speed = 2.5f * deltaTime;
			float radius = 10.0f;
			float camX = sin(glfwGetTime()) * radius;
			float camZ = cos(glfwGetTime()) * radius;
			//glm::mat4 view;
			//view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

			KeyboardInput(mywindow, cameraPos, cameraFront, cameraUp, speed);
			//view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
			shader.SetUniformMatrix4fv("view", view);



			//rend.DrawElements(va, ib, shader);
			for (int i = 0; i < 10; i++)
			{
				float angle = 50.0f;
				angle = glfwGetTime() * angle;
				model = glm::translate(glm::mat4(), cubePositions[i]);
				model = glm::rotate(model, glm::radians(50.0f), glm::vec3(1.0f, 0.3f, 0.5f));
				shader.SetUniformMatrix4fv("model", model);
				rend.DrawArrays(va, vb, layout, shader);
			}
			mywindow.Update();
		}
	}


	
	return 0;
}

