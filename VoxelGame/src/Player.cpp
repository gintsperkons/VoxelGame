#include "Player.h"
#include <iostream>
#include "WorldStructure/WorldManager.h"
#include "GUI/BaseElement.h"
#include "GUI/GUI_Manager.h"

void Player::updateWorld()
{
	currentWorld->PlayerUpdate(this);
}

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

	World::RaycastResult result = WorldManager::GetInstance()->GetWorld("testWorld")->Raycast(getPosition(), camera->GetFront(), 10.0f);

	if (result.hit)
	{
		
		BaseElement *tempEl = GUI_Manager::GetInstance()->GetChild("testLayout")->GetChild("HitBlockText");
		if (tempEl != nullptr)
		{
			Text *tempText = (Text *)tempEl;
			tempText->SetText(std::to_string(result.block->GetType()) + " x:" + std::to_string(result.position.x) +
							  " y:" + std::to_string(result.position.y) +
							  " z:" + std::to_string(result.position.z));
		}
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
	else
	{
		BaseElement *tempEl = GUI_Manager::GetInstance()->GetChild("testLayout")->GetChild("HitBlockText");
		if (tempEl != nullptr)
		{
			Text *tempText = (Text *)tempEl;
			tempText->SetText("No Block");
		}
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

void Player::ChangeWorld(std::string worldName)
{
	currentWorld = WorldManager::GetInstance()->GetWorld(worldName);
}

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
