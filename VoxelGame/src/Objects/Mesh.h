#pragma once
#include "../ShaderManager.h"
#include <GLAD/glad.h>
class Mesh
{
	unsigned int VAO, VBO, IBO;
	int indexCount;
	ShaderManager *shaderManager;
	glm::mat4 model;

	public:
	Mesh(ShaderManager *shaderManager);
	~Mesh();

	void Create(float *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void Render();
	void Clear();

};

