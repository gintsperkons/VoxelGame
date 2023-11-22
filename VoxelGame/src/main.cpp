#include <iostream>
#include <glad/glad.h>
#include "WindowManager.h"
#include "InputManager.h"
#include "ShaderManager.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "Objects/Mesh.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Player.h"
#include <GLM/glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>








float vertices[] = {
// positions          // colors           // texture coords
	//back
 0.0f,  0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,    
 0.0f,  1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   
 1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,   
 1.0f,  0.0f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,  
	//right
 1.0f,  0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
 1.0f,  1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
 1.0f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
 1.0f,  0.0f, 1.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	//front
 1.0f,  0.0f, 1.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
 1.0f,  1.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
 0.0f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
 0.0f,  0.0f, 1.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	//left
 0.0f,  0.0f, 1.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
 0.0f,  1.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
 0.0f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
 0.0f,  0.0f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	//top
 0.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
 0.0f,  1.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
 1.0f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
 1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	//bottom
 1.0f,  0.0f, 1.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
 1.0f,  0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
 0.0f,  0.0f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
 0.0f,  0.0f, 1.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f
};
unsigned int indices[] = {  // note that we start from 0!
	0, 2, 1,   
	0, 3, 2,    

	4, 6, 5,
	4, 7, 6,
	
	8, 10, 9,
	8, 11, 10,
	
	12, 14, 13,
	12, 15, 14,
	
	16, 18, 17,
	16, 19, 18,

	20, 21, 22,
	20, 22, 23
};



std::vector<Mesh> meshList;



int main()
{
	
	InputManager::GetInstance();
	WindowManager::GetInstance();
	ShaderManager::GetInstance();
	TextureManager::GetInstance();
	Camera * playerCamera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
	Player * player = new Player(playerCamera, InputManager::GetInstance(),5,0.1);
	InputManager::GetInstance()->Init();


	Mesh m1 = Mesh(ShaderManager::GetInstance());

	m1.Create(vertices, indices, 192, 36);
	meshList.push_back(m1);







	float lastFrame = 0.0f;
	float deltaTime = 0.0f;




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



		

		ShaderManager::GetInstance()->UseShader("solid");
		TextureManager::GetInstance()->UseTexture("default");
		

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (WindowManager::GetInstance()->getBufferWidth() / (float)WindowManager::GetInstance()->getBufferHeight()), 0.1f, 100.0f);

		ShaderManager::GetInstance()->SetMat4("projection",(&projection));
		glm::mat4 view = playerCamera->getViewMatrix();
		ShaderManager::GetInstance()->SetMat4("view",&view);



		for (int i = 0; i < meshList.size(); i++)
		{
			meshList[i].Render();
		}

		//Swap buffers
		WindowManager::GetInstance()->SwapBuffers();
		//Clear
		WindowManager::GetInstance()->Clear();


	}


	delete WindowManager::GetInstance();
	delete InputManager::GetInstance();
	delete ShaderManager::GetInstance();
	delete TextureManager::GetInstance();
	delete playerCamera;
	delete player;
	return 0;
}



