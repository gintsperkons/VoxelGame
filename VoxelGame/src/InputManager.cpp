#include <GLFW/glfw3.h>

#include <iostream>

#include "InputManager.h"
#include "WindowManager.h"


void InputManager::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	InputManager* input = static_cast<WindowManager*>(glfwGetWindowUserPointer(window))->GetInputManager();

	switch (action)
	{
	case GLFW_PRESS:
		input->keyStates[key] = KEY_PRESSED;
		break;
	case GLFW_RELEASE:
		input->keyStates[key] = KEY_RELEASED;
		break;
	}
}

void InputManager::MouseCallback(GLFWwindow *window, double xpos, double ypos)
{
	InputManager *input = static_cast<WindowManager *>(glfwGetWindowUserPointer(window))->GetInputManager();
	input->mousePosition = glm::vec2(xpos, ypos);
}

void InputManager::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	InputManager *input = static_cast<WindowManager *>(glfwGetWindowUserPointer(window))->GetInputManager();
	KeyCallback(window, button, 0, action, mods);
}

void InputManager::ScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
	InputManager *input = static_cast<WindowManager *>(glfwGetWindowUserPointer(window))->GetInputManager();
	input->scroll = (float)yoffset;
}



void InputManager::Update()
{
	scroll = 0.0f;
	prevMousePosition = mousePosition;

	UpdateKeyStates();
	glfwPollEvents();
}


void InputManager::UpdateKeyStates()
{
	for (auto it = keyStates.begin(); it != keyStates.end(); it++)
	{
		if (it->second == KEY_PRESSED)
			it->second = KEY_HELD;

		if (it->second == KEY_RELEASED)
			it->second = KEY_UP;
	}
}




InputManager::InputManager()
{
	
}

void InputManager::Init()
{
	double xPos, yPos;
	// Get mouse position
	glfwGetCursorPos(glfwGetCurrentContext(), &xPos, &yPos);
	mousePosition = glm::vec2(xPos, yPos);
	prevMousePosition = mousePosition;




	glfwSetKeyCallback(glfwGetCurrentContext(), &InputManager::KeyCallback);
	glfwSetCursorPosCallback(glfwGetCurrentContext(), &InputManager::MouseCallback);
	glfwSetMouseButtonCallback(glfwGetCurrentContext(), &InputManager::MouseButtonCallback);
	glfwSetScrollCallback(glfwGetCurrentContext(), &InputManager::ScrollCallback);

}

InputManager::~InputManager()
{}




bool InputManager::GetKeyPressed(int key)
{
	return keyStates[key] == KEY_PRESSED;
}

bool InputManager::GetKey(int key)
{
	const KeyState &state = keyStates[key];
	return state == KEY_PRESSED || state == KEY_HELD;
}

bool InputManager::GetKeyReleased(int key)
{
	return keyStates[key] == KEY_RELEASED;
}

glm::vec2 InputManager::GetDeltaMouse()
{
	return prevMousePosition - mousePosition;
}

float InputManager::GetScroll()
{
	return scroll;
}



