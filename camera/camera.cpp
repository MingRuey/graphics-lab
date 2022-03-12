
#include "camera.h"
#include <vector>

Camera::Camera(glm::uvec3 position, glm::vec3 up, float yaw, float pitch) 
	: Front(glm::vec3(0.0f, 0.0f, -1.0f)),MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) 
	: Front(glm::vec3(0.0f, 0.0f, -1.0f)),MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}
glm::mat4 Camera::getViewMatrix() 
{
	return glm::lookAt(Position, Position + Front, Up);
}
void Camera::processKeyBoard(Camera_Movement direction, float deltaTime) 
{
	float velocity = MovementSpeed * deltaTime;
	switch (direction)
	{
	case FORWARD:
		Position += Front * velocity;
		break;
	case BACKWARD:
		Position -= Front * velocity;
		break;
	case LEFT:
		Position -= RIGHT * velocity;
		break;
	case RIGHT:
		Position += RIGHT * velocity;
		break;
	default:
		break;
	}
}
void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) 
{
	xoffset *= xoffset;
	yoffset *= yoffset;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch) {
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}
	updateCameraVectors();
}
void Camera::processMouseScroll(float yoffset) 
{
	Zoom -= (float)yoffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}

void Camera::updateCameraVectors() 
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw) * cos(glm::radians(Pitch)));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw) * cos(glm::radians(Pitch)));
	Front = glm::normalize(front);
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}
