#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

class Camera
{
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw;
	float pitch;




public:
	Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
	~Camera();
	glm::vec3 GetPosition();
	glm::vec3 GetFront();
	glm::vec3 GetRight();
	glm::vec3 GetWorldUp();
	float GetYaw();
	float GetPitch();
	void SetYaw(float yaw);
	void SetPitch(float pitch);
	void SetPosition(glm::vec3 pos);
	void update();
	glm::mat4 getViewMatrix();

};

