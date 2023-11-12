#include <iostream>
#include <glad/glad.h>
#include "WindowManager.h"
#include "InputManager.h"
#include "ShaderManager.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "Objects/Mesh.h"
#include "TextureManager.h"








float vertices[] = {
// positions          // colors           // texture coords
 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};



std::vector<Mesh> meshList;



int main()
{
	InputManager *inputManager = new InputManager();
	WindowManager *windowManager = new WindowManager(inputManager);
	ShaderManager *shaderManager = new ShaderManager();
	TextureManager *textureManager = new TextureManager();

	inputManager->Init();


	Mesh m1 = Mesh();

	m1.Create(vertices, indices, 32, 6);
	meshList.push_back(m1);








	float lastFrame = 0.0f;
	float deltaTime = 0.0f;




	//Game loop
	while (!glfwWindowShouldClose(windowManager->GetWindow()))
	{
		//Delta time
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		float fps = 1.0f / deltaTime;




		//Updates
		inputManager->Update();
		windowManager->Update();




		

		shaderManager->UseShader("solid");


		textureManager->UseTexture("default");




		for (int i = 0; i < meshList.size(); i++)
		{
			meshList[i].Render();
		}

		//Swap buffers
		windowManager->SwapBuffers();
		//Clear
		windowManager->Clear();


	}


	delete windowManager;
	delete inputManager;
	delete shaderManager;
	delete textureManager;
	return 0;
}



