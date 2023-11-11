#pragma once
#include <GLAD/glad.h>
class Mesh
{
	unsigned int VAO, VBO, IBO;
	int indexCount;

	public:
	Mesh();
	~Mesh();

	void Create(float *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void Render();
	void Clear();

};

