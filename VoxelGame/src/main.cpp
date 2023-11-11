#include <iostream>
#include <glad/glad.h>
#include "WindowManager.h"
#include "InputManager.h"
#include "ShaderManager.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "Objects/Mesh.h"








float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
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
	inputManager->Init();


	Mesh m1 = Mesh();

	m1.Create(vertices, indices, 12, 6);
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




		//Render here
		if (shaderManager->shaderList.find("solid") == shaderManager->shaderList.end())
		{
			shaderManager->shaderList["base"]->UseShader();
		}
		else
		{
			shaderManager->shaderList["solid"]->UseShader();
		}

		


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
	return 0;
}



