#include "Block.h"
#include <iostream>
float vertices[] = {
// positions          // colors           // texture coords
	//back
 0.0f,  0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
 0.0f,  1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
 1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
 1.0f,  0.0f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	//right
 1.0f,  0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
 1.0f,  1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
 1.0f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
 1.0f,  0.0f, 1.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	//front
 1.0f,  0.0f, 1.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
 1.0f,  1.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
 0.0f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
 0.0f,  0.0f, 1.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	//left
 0.0f,  0.0f, 1.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
 0.0f,  1.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
 0.0f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
 0.0f,  0.0f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	//top
 0.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
 0.0f,  1.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
 1.0f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
 1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	//bottom
 1.0f,  0.0f, 1.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
 1.0f,  0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
 0.0f,  0.0f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
 0.0f,  0.0f, 1.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f
};
unsigned int indices[] = {  // note that we start from 0!
	0, 2, 1,
	0, 3, 2,

	4, 6, 5,
	4, 7, 6,

	8, 10, 9,
	8, 11, 10,

	12, 14, 13,
	12, 15, 14,

	16, 18, 17,
	16, 19, 18,

	20, 21, 22,
	20, 22, 23
};


Block::Block():position(glm::vec3(0.0f, 0.0f, 0.0f)),
axis(glm::vec3(0.0f, 1.0f, 0.0f)),
angle(0.0f),
scale(glm::vec3(1.0f, 1.0f, 1.0f))
{


}

Block::~Block()
{
	Clear();
}

void Block::Create(glm::vec3 pos)
{
	position = pos;
	Mesh::Create(vertices, indices, 192, 36);
}

void Block::Render()
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, angle, axis);
	model = glm::scale(model, scale);
	Mesh::Render();
	shaderManager->SetMat4("model", &model);
}

void Block::Clear()
{
	

	Mesh::Clear();
}

void Block::Move(glm::vec3 position)
{
	this->position+= position;
}

void Block::SetRotation(float angle, glm::vec3 axis)
{
	this->angle = angle;
	this->axis = axis;
}

void Block::SetScale(glm::vec3 scale)
{
	this->scale = scale;
}
