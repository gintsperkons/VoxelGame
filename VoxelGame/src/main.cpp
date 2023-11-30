#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <glad/glad.h>
#include "WindowManager.h"
#include "InputManager.h"
#include "ShaderManager.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "Objects/Mesh.h"
#include "Objects/Block.h"
#include "TextureManager.h"
#include "WorldStructure/WorldManager.h"
#include "SkyBox.h"
#include "Camera.h"
#include "Player.h"
#include "GUI/GUI_Manager.h"
#include <GLM/glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <thread>
#include "WorldStructure/Generator/TerrainGenerator.h"

#include "GUI/Text.h"
#include "Objects/Line.h"


float deltaTime;
Player *player;







std::vector<Block *> meshList;



void renderLoop()
{}


void worldGenLoop()
{
	while (!glfwWindowShouldClose(WindowManager::GetInstance()->GetWindow()))
	{
		WorldManager::GetInstance()->Update(deltaTime);
		player->updateWorld();
	}
}



int main()
{

	InputManager::GetInstance();
	WindowManager::GetInstance();
	ShaderManager::GetInstance();
	TextureManager::GetInstance();
	GUI_Manager::GetInstance();
	SkyBox::GetInstance();
	WorldManager::GetInstance();
	InputManager::GetInstance()->Init();
	SkyBox::GetInstance()->Create();

	//create gui elements
	Text *fpsText = GUI_Manager::GetInstance()->CreateTextElement("debugText");
	Text *locationText = GUI_Manager::GetInstance()->CreateTextElement("locationText");
	Text *chunkLocText = GUI_Manager::GetInstance()->CreateTextElement("chunkLocText");
	Text *hitBlockText = GUI_Manager::GetInstance()->CreateTextElement("HitBlockText");
	fpsText->SetPadding(5, 5, 5, 5);
	locationText->SetPadding(5, 5, 5, 5);
	chunkLocText->SetPadding(5, 5, 5, 5);
	hitBlockText->SetPadding(5, 5, 5, 5);
	VerticalLayout *layout = GUI_Manager::GetInstance()->CreateVerticalLayout("testLayout");
	layout->AddElement(fpsText);
	layout->AddElement(locationText);
	layout->AddElement(chunkLocText);
	layout->AddElement(hitBlockText);
	GUI_Manager::GetInstance()->AddElement(layout);

	WorldManager::GetInstance()->CreateWorld("testWorld");


	


	Camera *playerCamera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
	player = new Player(playerCamera, InputManager::GetInstance(), 5, 0.1);
	player->ChangeWorld("testWorld");



	float lastFrame = 0.0f;


	ShaderManager::GetInstance()->UseShader("solid");
	TextureManager::GetInstance()->UseTexture("andesite");
	WorldManager::GetInstance()->AddPlayer("testWorld", player);

	std::vector<Line*> lines;
	Line* line = new Line(glm::vec3(0, 0, 0), glm::vec3(10, 10, 10), glm::vec3(0, 1, 0));
	lines.push_back(line);


	std::thread worldGenThread(worldGenLoop);

	//Game loop
	while (!glfwWindowShouldClose(WindowManager::GetInstance()->GetWindow()))
	{
		//Delta time
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		float fps = 1.0f / deltaTime;

		glm::vec3 pos = player->getPosition();
		glm::vec2 currChunk = Chunk::WorldToChunkCord(pos);

		fpsText->SetText(std::to_string((int)round(fps)) + " fps");
		locationText->SetText("x:" + std::to_string(pos.x) + " y:" + std::to_string(pos.y) + " z:" + std::to_string(pos.z));
		chunkLocText->SetText("chunkX:" + std::to_string((int)currChunk.x) + " chunkZ:" + std::to_string((int)currChunk.y));

		TextureManager::GetInstance()->UseTexture("andesite");
		ShaderManager::GetInstance()->UseShader("solid");



		//Updates
		InputManager::GetInstance()->Update();
		WindowManager::GetInstance()->Update();

		player->update(deltaTime);




		glm::mat4 projection = glm::perspective(glm::radians(90.0f), (WindowManager::GetInstance()->getBufferWidth() / (float)WindowManager::GetInstance()->getBufferHeight()), 0.1f, 100.0f);
		glm::mat4 view = playerCamera->getViewMatrix();
		ShaderManager::GetInstance()->SetMat4("projection", &projection);
		ShaderManager::GetInstance()->SetMat4("view", &view);


		//Draw sky
		SkyBox::GetInstance()->Render(view, projection);

		//Draw else


		TextureManager::GetInstance()->UseTexture("andesite");
		ShaderManager::GetInstance()->UseShader("solid");
		WorldManager::GetInstance()->Render();



		GUI_Manager::GetInstance()->Render();


	

	


		ShaderManager::GetInstance()->UseShader("line");
		ShaderManager::GetInstance()->SetMat4("projection", &projection);
		ShaderManager::GetInstance()->SetMat4("view", &view);

		for(Line *l : lines)
			l->Render();

		
		//Swap buffers
		WindowManager::GetInstance()->SwapBuffers();
		//Clear
		WindowManager::GetInstance()->Clear();


	}

	worldGenThread.join();

	for (int i = 0; i < meshList.size(); i++)
	{
		delete meshList[i];
	}
	for (int i = 0; i < lines.size(); i++)
	{
		delete lines[i];
	}
	delete WindowManager::GetInstance();
	delete InputManager::GetInstance();
	delete ShaderManager::GetInstance();
	delete TextureManager::GetInstance();
	delete SkyBox::GetInstance();
	delete WorldManager::GetInstance();
	delete GUI_Manager::GetInstance();
	delete playerCamera;
	delete player;


	return 0;
}



