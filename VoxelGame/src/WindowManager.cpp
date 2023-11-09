#include <iostream>
#include <GLAD/glad.h>
#include "WindowManager.h"
#include "InputManager.h"

void WindowManager::ResizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow *WindowManager::GetWindow()
{
	return this->window;
}

InputManager *WindowManager::GetInputManager()
{
	return this->inputManager;
}

void WindowManager::Clear()
{
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void WindowManager::SwapBuffers()
{
	glfwSwapBuffers(this->window);
}

bool WindowManager::ShouldClose()
{
	return glfwWindowShouldClose(this->window);
}

void WindowManager::Update()
{
	if (inputManager->GetKeyPressed(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, true);

}



WindowManager::WindowManager(InputManager *inputManager) : window(nullptr),
resolution(800, 600),
title("VoxelGame"),
clearColor(0.2f, 0.5f, 0.2f, 1.0f),
inputManager(inputManager)
{

	//Initialize GLFW and set window hints
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create window
	this->window = glfwCreateWindow(resolution.x, resolution.y, title.c_str(), NULL, NULL);

	//Exit if window creation fails
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	//Set window to current context
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, ResizeCallback);



	//Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}

	//Tell OpenGL the size of the rendering window

	glViewport(0, 0, resolution.x, resolution.y);


}

WindowManager::~WindowManager()
{

	glfwTerminate();
}