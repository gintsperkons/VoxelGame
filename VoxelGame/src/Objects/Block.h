#pragma once
#include "Mesh.h"
#include <GLM/glm.hpp>

class Block: public Mesh
{
	glm::vec3 position;
	glm::vec3 axis;
	float angle;
	glm::vec3 scale;
	std::string type;
	bool readyToRender;

public:
	enum BlockType : unsigned int
	{
		Block_Air = 0,
		Block_Stone = 1,
	};


	Block();
	~Block();

	void Create(glm::vec3 pos, std::string type);
	void CreateGLItems();
	void Render();
	void Clear();
	void Move(glm::vec3 position);
	void SetRotation(float angle, glm::vec3 axis);
	void SetScale(glm::vec3 scale);

	void ChangeType(BlockType type);

	


	std::string GetType();
};

