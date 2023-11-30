#include <iostream>
#include <GLAD/glad.h>
#include "WindowManager.h"
#include "InputManager.h"

static WindowManager *instance = nullptr;
WindowManager *WindowManager::GetInstance()
{
	if (instance == nullptr)
		instance = new WindowManager();
	return instance;
}

void WindowManager::ResizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
	WindowManager *wm = static_cast<WindowManager *>(glfwGetWindowUserPointer(window));
	glfwGetFramebufferSize(window, &wm->bufferWidth, &wm->bufferHeight);
}

void WindowManager::ChangePolygonMode()
{
	int polygonMode;
	glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
	if (polygonMode == GL_LINE)
	{
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (polygonMode == GL_FILL)
	{
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}

void WindowManager::ChangeFullscreen()
{
	fullscreen = !fullscreen;
	if (IsFullscreen() == fullscreen)
	{
		return;
	}
	if (fullscreen)
	{
		// get resolution of monitor
		GLFWmonitor *monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode *mode = glfwGetVideoMode(monitor);

		// backup window position and window size
		glfwGetWindowPos(window, &savedPos[0], &savedPos[1]);
		glfwGetWindowSize(window, &savedSize[0], &savedSize[1]);
		// switch to full screen
		glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, 0);
	}
	else
	{
	// restore last window size and position
		glfwSetWindowMonitor(window, nullptr, savedPos[0], savedPos[1], savedSize[0], savedSize[1], 0);
	}

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
	glClear(GL_DEPTH_BUFFER_BIT);
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
	if (inputManager->GetKeyPressed(GLFW_KEY_F4))
	{
		ChangePolygonMode();
	}
	if (inputManager->GetKeyPressed(GLFW_KEY_F11))
	{
		ChangeFullscreen();
	}




}



WindowManager::WindowManager() : window(nullptr),
resolution(800, 600),
title("VoxelGame"),
clearColor(0.0f, 0.0f, 0.0f, 1.0f),
inputManager(InputManager::GetInstance())
{

	//Initialize GLFW and set window hints
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

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
	//Hide cursor                                    
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);



	//Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}
	//Set OpenGL options
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//Tell OpenGL the size of the rendering window

	glViewport(0, 0, resolution.x, resolution.y);

	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
}


bool WindowManager::IsFullscreen()
{
	return glfwGetWindowMonitor(window) != nullptr;
}

WindowManager::~WindowManager()
{

	glfwTerminate();
}
