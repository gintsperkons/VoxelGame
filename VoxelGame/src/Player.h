#pragma once
#include "Camera.h"
#include "InputManager.h"
#include <GLM/glm.hpp>

class Player
{
	Camera *camera;
	InputManager *inputManager;
	glm::vec3 position;
	float movementSpeed;
	float turnSpeed;



	void updateKeyInput(float deltaTime);
	void updateMouseInput();
	public:
		Player(Camera *camera, InputManager* inputManager, float movementSpeed, float turnSpeed);
		~Player();
		void update(float deltaTime);
		glm::vec3 getPosition();
		Camera *getCamera();
};

