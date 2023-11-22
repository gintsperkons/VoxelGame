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
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg"
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

static SkyBox* instance = 0;
SkyBox::SkyBox()
{
	texturePath = std::filesystem::current_path().string() + "\\Textures";
}
void SkyBox::Create()
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);


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
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    skyMesh = new Mesh();
    skyMesh->Create(skyboxVertices, skyboxIndices, 64, 36);
}

void SkyBox::Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	viewMatrix = glm::mat4(glm::mat3(viewMatrix));
	glDepthMask(GL_FALSE);
	glDisable(GL_CULL_FACE);

	ShaderManager::GetInstance()->UseShader("skyBox");


	ShaderManager::GetInstance()->SetMat4("projection", &projectionMatrix);
	ShaderManager::GetInstance()->SetMat4("view", &viewMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	skyMesh->Render();

	glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
}

void SkyBox::Clear()
{
    delete skyMesh;
}


SkyBox::~SkyBox()
{
    Clear();
}
SkyBox *SkyBox::GetInstance()
{
	if (instance == nullptr)
		instance = new SkyBox();
	return instance;
}
