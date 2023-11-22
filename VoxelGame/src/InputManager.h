#pragma once
#include <GLM/glm.hpp>

#include <map>


class WindowManager;
class InputManager
{
private:


	float scroll;
	glm::vec2 mousePosition;
	glm::vec2 prevMousePosition;


	enum KeyState
	{
		KEY_UP,
		KEY_PRESSED,
		KEY_HELD,
		KEY_RELEASED,
	};


	std::map<int, KeyState> keyStates;



	static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void MouseCallback(GLFWwindow *window, double xpos, double ypos);
	static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
	static void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset);



public:


	InputManager();
	void Init();
	void Update();
	void UpdateKeyStates();
	~InputManager();

	bool GetKeyPressed(int key);
	bool GetKey(int key);
	bool GetKeyReleased(int key);
	glm::vec2 GetDeltaMouse();
	float GetScroll();


	static InputManager* GetInstance();
};

