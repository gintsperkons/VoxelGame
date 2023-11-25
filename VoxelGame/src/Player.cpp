#include <GLFW\glfw3.h>
#include "Player.h"
#include <iostream>

void Player::updateKeyInput(float deltaTime)
{
	GLfloat velocity = movementSpeed * deltaTime;


	if (inputManager->GetKey(GLFW_KEY_SPACE))
	{
		position += camera->GetWorldUp() * velocity;
	}
	if (inputManager->GetKey(GLFW_KEY_LEFT_SHIFT))
	{
		position -= camera->GetWorldUp() * velocity;
	}

	if (inputManager->GetKey(GLFW_KEY_W))
	{
		position += camera->GetFront() * velocity;
	}


	if (inputManager->GetKey(GLFW_KEY_S))
	{
		position -= camera->GetFront() * velocity;
	}

	if (inputManager->GetKey(GLFW_KEY_A))
	{
		position -= camera->GetRight() * velocity;
	}

	if (inputManager->GetKey(GLFW_KEY_D))
	{
		position += camera->GetRight() * velocity;
	}

}

void Player::updateMouseInput()
{	
	glm::vec2 mouseDelta = inputManager->GetDeltaMouse();

	float xChange = mouseDelta.x * turnSpeed;
	float yChange = mouseDelta.y * turnSpeed;

	float yaw = camera->GetYaw()-xChange;
	float pitch = camera->GetPitch() + yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}


	camera->SetYaw(yaw);
	camera->SetPitch(pitch);

}

Player::Player(Camera *camera, InputManager* inputManager,float movementSpeed,float turnSpeed)
{
	this->inputManager = inputManager;
	this->camera = camera;
	this->position = camera->GetPosition();
	this->movementSpeed = movementSpeed;
	this->turnSpeed = turnSpeed;
	this->renderDistance = 3;
}

Player::~Player()
{}

void Player::update(float deltaTime)
{	
	updateKeyInput(deltaTime);
	updateMouseInput();

	camera->SetPosition(position);
	camera->update();
}

glm::vec3 Player::getPosition()
{
	return position;
}

Camera *Player::getCamera()
{
	return camera;
}

int Player::getRenderDistance()
{
	return renderDistance;
}
