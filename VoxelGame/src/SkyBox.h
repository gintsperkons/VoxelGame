#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <string>
class Mesh;

class SkyBox
{
	unsigned int textureID;
	Mesh *skyMesh;
	std::string texturePath;

public:


	SkyBox();
	void Create();
	void Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	void Clear();
	~SkyBox();
	

	static SkyBox *GetInstance();
};

