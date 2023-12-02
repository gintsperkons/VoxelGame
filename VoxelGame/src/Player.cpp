#include "Player.h"
#include <iostream>
#include "WorldStructure/WorldManager.h"
#include "GUI/BaseElement.h"
#include "GUI/GUI_Manager.h"

// update player's world from player's position
void Player::updateWorld()
{
	currentWorld->PlayerUpdate(this);
}

// update key input
void Player::updateKeyInput(float deltaTime)
{
	GLfloat velocity = movementSpeed * deltaTime;

	//move direction calculations
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

	//raycast test for block hit
	World::RaycastResult result = WorldManager::GetInstance()->GetWorld("testWorld")->Raycast(getPosition(), camera->GetFront(), 10.0f);
	
	if (result.hit)
	{
		// if block hit, update text element to hit block info
		BaseElement *tempEl = GUI_Manager::GetInstance()->GetChild("testLayout")->GetChild("HitBlockText");
		if (tempEl != nullptr)
		{
			Text *tempText = (Text *)tempEl;
			tempText->SetText(std::to_string(result.block->GetType()) + " x:" + std::to_string(result.position.x) +
							  " y:" + std::to_string(result.position.y) +
							  " z:" + std::to_string(result.position.z));
		}
		// if mouse button pressed, remove or place block
		if (inputManager->GetKeyPressed(GLFW_MOUSE_BUTTON_1))
		{
			std::cout << "Mouse 1" << std::endl;
			currentWorld->RemoveBlock(result.position + result.normal*-0.5f);
		}
		if (inputManager->GetKeyPressed(GLFW_MOUSE_BUTTON_2))
		{
			std::cout << "Mouse 2" << std::endl;
			currentWorld->PlaceBlock(result.position + result.normal * 0.5f, Block::BlockType::Block_Stone);
		}
	}
	else // if no block hit, update text element to no block
	{
		BaseElement *tempEl = GUI_Manager::GetInstance()->GetChild("testLayout")->GetChild("HitBlockText");
		if (tempEl != nullptr)
		{
			Text *tempText = (Text *)tempEl;
			tempText->SetText("No Block");
		}
	}

	

}

// update mouse input 
void Player::updateMouseInput()
{	

	
	glm::vec2 mouseDelta = inputManager->GetDeltaMouse();

	//calculate change in x and y
	float xChange = mouseDelta.x * turnSpeed;
	float yChange = mouseDelta.y * turnSpeed;

	//calculate new yaw and pitch
	float yaw = camera->GetYaw()-xChange;
	float pitch = camera->GetPitch() + yChange;

	//clamp pitch to prevent camera flipping over itself 
	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	//set new yaw and pitch
	camera->SetYaw(yaw);
	camera->SetPitch(pitch);

}


Player::Player(Camera *camera, InputManager* inputManager,float movementSpeed,float turnSpeed)
{	
	//set variables
	this->inputManager = inputManager;
	this->camera = camera;
	this->position = camera->GetPosition();
	this->movementSpeed = movementSpeed;
	this->turnSpeed = turnSpeed;
	this->renderDistance = 3;
}

Player::~Player()
{}

// change player's world to world with name worldName 
void Player::ChangeWorld(std::string worldName)
{
	currentWorld = WorldManager::GetInstance()->GetWorld(worldName);
}

// update player 
void Player::update(float deltaTime)
{	
	//update player's position and camera
	updateKeyInput(deltaTime);
	updateMouseInput();

	camera->SetPosition(position);
	camera->update();
	//update player's world
	updateWorld();

}

// get player's position
glm::vec3 Player::getPosition()
{
	return position;
}

// get player's camera
Camera *Player::getCamera()
{
	return camera;
}

// get player's render distance
int Player::getRenderDistance()
{
	return renderDistance;
}
