#pragma once
#include "WorldStructure/World.h"
#include "Camera.h"
#include "InputManager.h"
#include <GLM/glm.hpp>

class World;

class Player
{
	Camera *camera;
	InputManager *inputManager;
	glm::vec3 position;
	float movementSpeed;
	float turnSpeed;
	int renderDistance;
	World* currentWorld;


	void updateKeyInput(float deltaTime);
	void updateMouseInput();
	public:
		Player(Camera *camera, InputManager* inputManager, float movementSpeed, float turnSpeed);
		~Player();
		void ChangeWorld(std::string worldName);
		void updateWorld();
		void update(float deltaTime);
		glm::vec3 getPosition();
		Camera *getCamera();
		int getRenderDistance();
};

