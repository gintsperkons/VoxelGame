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
#include <GLM/glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <thread>


float deltaTime;








std::vector<Block*> meshList;



void renderLoop()
{
}


void worldGenLoop()
{
	while (!glfwWindowShouldClose(WindowManager::GetInstance()->GetWindow()))
	{
		WorldManager::GetInstance()->Update(deltaTime);
	}
}



int main()
{
	
	InputManager::GetInstance();
	WindowManager::GetInstance();
	ShaderManager::GetInstance();
	TextureManager::GetInstance();
	SkyBox::GetInstance();
	WorldManager::GetInstance();
	Camera * playerCamera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
	Player * player = new Player(playerCamera, InputManager::GetInstance(),5,0.1);
	InputManager::GetInstance()->Init();
	SkyBox::GetInstance()->Create();



	







	float lastFrame = 0.0f;


	ShaderManager::GetInstance()->UseShader("solid");
	TextureManager::GetInstance()->UseTexture("andesite");
	WorldManager::GetInstance()->CreateWorld("testWorld");
	WorldManager::GetInstance()->AddPlayer("testWorld",player);



	std::thread worldGenThread(worldGenLoop);

	//Game loop
	while (!glfwWindowShouldClose(WindowManager::GetInstance()->GetWindow()))
	{
		//Delta time
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		float fps = 1.0f / deltaTime;




		//Updates
		InputManager::GetInstance()->Update();
		WindowManager::GetInstance()->Update();

		player->update(deltaTime);



		


		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (WindowManager::GetInstance()->getBufferWidth() / (float)WindowManager::GetInstance()->getBufferHeight()), 0.1f, 100.0f);
		glm::mat4 view = playerCamera->getViewMatrix();
		ShaderManager::GetInstance()->SetMat4("projection",&projection);
		ShaderManager::GetInstance()->SetMat4("view",&view);



		//Draw sky
		SkyBox::GetInstance()->Render(view, projection);

		//Draw else



		ShaderManager::GetInstance()->UseShader("solid");
		TextureManager::GetInstance()->UseTexture("andesite");
		WorldManager::GetInstance()->Render();

		


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
	delete WindowManager::GetInstance();
	delete InputManager::GetInstance();
	delete ShaderManager::GetInstance();
	delete TextureManager::GetInstance();
	delete SkyBox::GetInstance();
	delete WorldManager::GetInstance();
	delete playerCamera;
	delete player;


	return 0;
}



