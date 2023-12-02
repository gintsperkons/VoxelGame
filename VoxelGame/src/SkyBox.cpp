#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GLAD/glad.h>
#include "SkyBox.h"
#include "ShaderManager.h"
#include "Objects/Mesh.h"
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

std::vector<std::string> faces
{
		"right.png",
		"left.png",
		"top.png",
		"bottom.png",
		"front.png",
		"back.png"
};

// Mesh Setup 
unsigned int skyboxIndices[] = {
	// front
	0, 1, 2,
	2, 1, 3,
	// right
	2, 3, 5,
	5, 3, 7,
	// back
	5, 7, 4,
	4, 7, 6,
	// left
	4, 6, 0,
	0, 6, 1,
	// top
	4, 0, 5,
	5, 0, 2,
	// bottom
	1, 6, 3,
	3, 6, 7
};

// skybox vertices
float skyboxVertices[] = {
	-1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
	-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
	1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
	1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,

	-1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
	-1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
	1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f
};

//singleton instance of skybox 
static SkyBox* instance = 0;
SkyBox *SkyBox::GetInstance()
{
	if (instance == nullptr)
		instance = new SkyBox();
	return instance;
}


SkyBox::SkyBox()
{
	//set texture path
	texturePath = std::filesystem::current_path().string() + "\\Textures";
}
void SkyBox::Create()
{
	//load texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	//load texture data
    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load((texturePath +"\\skybox\\" + faces[i]).c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
            stbi_image_free(data);
    }
	//set texture parameters
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	//create mesh for skybox
    skyMesh = new Mesh();
    skyMesh->Create(skyboxVertices, skyboxIndices, 64, 36);
}

//render skybox with skybox shader 
void SkyBox::Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	//remove translation from view matrix to make skybox static
	viewMatrix = glm::mat4(glm::mat3(viewMatrix));
	bool faceCullEnabled = glIsEnabled(GL_CULL_FACE);
	glDepthMask(GL_FALSE);
	glDisable(GL_CULL_FACE);

	//use skybox shader
	ShaderManager::GetInstance()->UseShader("skyBox");


	//set view and projection matrices
	ShaderManager::GetInstance()->SetMat4("projection", &projectionMatrix);
	ShaderManager::GetInstance()->SetMat4("view", &viewMatrix);

	//bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	//render skybox
	skyMesh->Render();

	//reset culling and depth mask
	if (faceCullEnabled)
		glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
}


//delete skybox mesh
void SkyBox::Clear()
{
    delete skyMesh;
}


SkyBox::~SkyBox()
{
    Clear();
}