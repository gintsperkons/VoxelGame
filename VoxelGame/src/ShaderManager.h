#pragma once
#include <string>
#include <map>
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Shader;

class ShaderManager
{
private:
	std::string shaderPath;
	Shader* currentShader;
	std::string getShaderName(std::string vertexFileName, std::string FragmentFileName);

public:
	std::map<std::string, Shader*> shaderList;

	ShaderManager();

	void CreateFromFiles(const char *vertexLocation, const char *fragmentLocation);

	void UseShader(std::string shaderName);
	void SetMat4(std::string type, glm::mat4 *matrix);
	void ClearShaderList();
	~ShaderManager();




	private:
		//Base shader for if no file found
	// Vertex Shader
		const char *vShader = "                                                \n\
#version 330                                                                  \n\
                                                                              \n\
layout (location = 0) in vec3 pos;											  \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);				  \n\
}";

// Fragment Shader
		const char *fShader = "                                                \n\
#version 330                                                                  \n\
                                                                              \n\
out vec4 colour;                                                               \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    colour = vec4(1.0, 0.0, 0.0, 1.0);                                         \n\
}";
};



