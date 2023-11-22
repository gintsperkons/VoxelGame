#pragma once
#include "../ShaderManager.h"
#include <GLAD/glad.h>
class Mesh
{
	unsigned int VAO, VBO, IBO;
	int indexCount;
	

	protected:
		ShaderManager *shaderManager;
		glm::mat4 model;

	public:
	Mesh();
	~Mesh();

	void Create(float *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void Render();
	void Clear();
	unsigned int GetVAO();
};

