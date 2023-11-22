#pragma once
#include "Mesh.h"
#include <GLM/glm.hpp>

class Block: public Mesh
{
	glm::vec3 position;
	glm::vec3 axis;
	float angle;
	glm::vec3 scale;


public:
	Block();
	~Block();

	void Create(glm::vec3 pos);
	void Render();
	void Clear();
	void Move(glm::vec3 position);
	void SetRotation(float angle, glm::vec3 axis);
	void SetScale(glm::vec3 scale);
};

