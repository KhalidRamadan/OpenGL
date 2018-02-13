#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace game
{
	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	// Default camera values
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 2.5f;
	const float SENSITIVTY = 0.1f;
	const float ZOOM = 45.0f;
	class Camera
	{
	public:
		// Camera Attributes
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;
		// Eular Angles
		float Yaw;
		float Pitch;
		// Camera options
		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;

		//Window *win = (Window*)glfwGetWindowUserPointer(window);
		//// Constructor with vectors
		//Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		//	   glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),float yaw = YAW, float pitch = PITCH) : 
		//	Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
		//{
		//	Position = position;
		//	WorldUp = up;
		//	Yaw = yaw;
		//	Pitch = pitch;
		//	updateCameraVectors();
		//}
		//
		//glm::mat4 GetViewMatrix()
		//{
		//	return glm::lookAt(Position, Position + Front, Up);
		//}
		//void KeyboardInput(const Window &window, glm::vec3 &cameraPos,
		//	const glm::vec3 &cameraFront, const glm::vec3 &cameraUp, float cameraSpeed);
	};

}