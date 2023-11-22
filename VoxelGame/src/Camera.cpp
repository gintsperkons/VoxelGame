#include "Camera.h"
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
{
	this->position = position;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;

	this->front = glm::vec3(0.0f, 0.0f, -1.0f);

	this->update();
}




void Camera::update()
{
	this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front.y = sin(glm::radians(this->pitch));
	this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	this->front = glm::normalize(this->front);


	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));



}



Camera::~Camera()
{

}

glm::vec3 Camera::GetPosition()
{
	return this->position;
}
glm::vec3 Camera::GetFront()
{
	return this->front;
}
glm::vec3 Camera::GetRight()
{
	return this->right;
}

float Camera::GetPitch()
{
	return this->pitch;
}

float Camera::GetYaw()
{
	return this->yaw;
}
glm::vec3 Camera::GetWorldUp()
{
	return this->worldUp;
}

void Camera::SetPitch(float pitch)
{
	this->pitch = pitch;
}

void Camera::SetYaw(float yaw)
{
	this->yaw = yaw;
}

 void Camera::SetPosition(glm::vec3 pos)
{
	this->position = pos;
	
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(this->position, this->position + this->front, this->up);
}
