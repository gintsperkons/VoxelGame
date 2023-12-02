
#include <iostream>

#include "InputManager.h"
#include "WindowManager.h"

// Singleton instance of InputManager class (only one instance of InputManager can exist) 
static InputManager *instance = nullptr;
InputManager *InputManager::GetInstance()
{
	if (instance == nullptr)
		instance = new InputManager();
	return instance;
}

// Callbacks for GLFW events (static functions) 
//keyboard callback function 
void InputManager::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	//gets the input manager from the window
	InputManager *input = static_cast<WindowManager *>(glfwGetWindowUserPointer(window))->GetInputManager();

	//sets the key state to pressed or released
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

//mouse callback function
void InputManager::MouseCallback(GLFWwindow *window, double xpos, double ypos)
{
	//gets the input manager from the window and sets the mouse position
	InputManager *input = static_cast<WindowManager *>(glfwGetWindowUserPointer(window))->GetInputManager();
	input->mousePosition = glm::vec2(xpos, ypos);
}

//mouse button callback function
void InputManager::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	//gets the input manager from the window and calls the key callback function
	InputManager *input = static_cast<WindowManager *>(glfwGetWindowUserPointer(window))->GetInputManager();
	KeyCallback(window, button, 0, action, mods);
}

//scroll callback function
void InputManager::ScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
	//gets the input manager from the window and sets the scroll value
	InputManager *input = static_cast<WindowManager *>(glfwGetWindowUserPointer(window))->GetInputManager();
	input->scroll = (float)yoffset;
}


// Update function
void InputManager::Update()
{
	// Reset scroll value and previous mouse position
	scroll = 0.0f;
	prevMousePosition = mousePosition;
	// Update key states (pressed, held, released) and poll events
	UpdateKeyStates();
	glfwPollEvents();
}

// Update key states (pressed >> held, released >> up)
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




void InputManager::Init()
{
	double xPos, yPos;
	// Get mouse position and set previous mouse position
	glfwGetCursorPos(glfwGetCurrentContext(), &xPos, &yPos);
	mousePosition = glm::vec2(xPos, yPos);
	prevMousePosition = mousePosition;



	// Set callbacks for GLFW events (keyboard, mouse, scroll)
	glfwSetKeyCallback(glfwGetCurrentContext(), &InputManager::KeyCallback);
	glfwSetCursorPosCallback(glfwGetCurrentContext(), &InputManager::MouseCallback);
	glfwSetMouseButtonCallback(glfwGetCurrentContext(), &InputManager::MouseButtonCallback);
	glfwSetScrollCallback(glfwGetCurrentContext(), &InputManager::ScrollCallback);

}

InputManager::~InputManager()
{}



// Getters for key states, mouse position cahnge, scroll value
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



