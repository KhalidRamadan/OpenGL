

// 3D FPS

#if 0 

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 6.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


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





#endif


