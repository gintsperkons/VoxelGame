#include <iostream>
#include "WindowManager.h"
#include "InputManager.h"




int main()
{
	InputManager *inputManager = new InputManager();
	WindowManager *windowManager = new WindowManager(inputManager);

	inputManager->Init();


	float lastFrame = 0.0f;
	float deltaTime = 0.0f;


	//Game loop
	while (!glfwWindowShouldClose(windowManager->GetWindow()))
	{
		//Delta time
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//std::cout << 1.0f / deltaTime << std::endl;
		
		//Updates
		inputManager->Update();
		windowManager->Update();




		//Draw
		windowManager->Clear();
		//Render here


	
		windowManager->SwapBuffers();


	}


	delete windowManager;
	delete inputManager;
	return 0;
}



