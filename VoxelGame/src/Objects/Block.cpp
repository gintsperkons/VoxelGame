#include "Block.h"
static float vertices[] = {
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
static unsigned int indices[] = {  // note that we start from 0!
	//triangle coners from vertices row is index
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


Block::Block() :position(glm::vec3(0.0f, 0.0f, 0.0f)),
axis(glm::vec3(0.0f, 1.0f, 0.0f)),
angle(0.0f),
scale(glm::vec3(1.0f, 1.0f, 1.0f)),
type(BlockType::Block_Air()),
readyToRender(false)
{


}

Block::~Block()
{
	Clear();
}

//create block with position and type 
void Block::Create(glm::vec3 pos, BlockType type)
{
	this->type = type;
	this->position = pos;
	readyToRender = false;
}

//create gl items for block 
void Block::CreateGLItems()
{
	Mesh::Create(vertices, indices, 192, 36);
	readyToRender = true;
}

//render block
void Block::Render()
{
	//if block is not ready to render create gl items
	if (!readyToRender)
	{
		CreateGLItems();
		return;
	}
	glm::mat4 model(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, angle, axis);
	model = glm::scale(model, scale);
	//set model matrix to active shader and render blocks mesh
	shaderManager->SetMat4("model", &model);
	Mesh::Render();

}

//clear blocks data
void Block::Clear()
{
	Mesh::Clear();
}

//move block
void Block::Move(glm::vec3 position)
{
	this->position += position;
}

//set rotation for block
void Block::SetRotation(float angle, glm::vec3 axis)
{
	this->angle = angle;
	this->axis = axis;
}

//set scale for block
void Block::SetScale(glm::vec3 scale)
{
	this->scale = scale;
}

//change block type
void Block::ChangeType(BlockType type)
{
	this->type = type;
}

// get block type
Block::BlockType Block::GetType()
{
	return BlockType(this->type);
}
