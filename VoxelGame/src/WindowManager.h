#pragma once

#define GLFW_INCLUDE_NONE
#include <string>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class InputManager;

class WindowManager
{
	GLFWwindow * window;
	glm::ivec2 resolution;
	glm::vec4 clearColor;
	std::string title;
	InputManager *inputManager;
	int bufferWidth;
	int bufferHeight;


	static void ResizeCallback(GLFWwindow *window, int width, int height);

public:
	GLFWwindow *GetWindow();
	InputManager *GetInputManager();

	void Clear();
	void SwapBuffers();
	bool ShouldClose();

	void Update();

	WindowManager();
	 ~WindowManager();


	 int getBufferWidth()
	 {
		 return bufferWidth;
	 }
	 int getBufferHeight()
	 {
		 return bufferHeight;
	 }

	 static WindowManager *GetInstance();
};

