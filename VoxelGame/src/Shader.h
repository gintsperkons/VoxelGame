#pragma once
#include <string>
#include <map>

class Shader
{
	std::string name;
	unsigned int shaderID, uniformProjection, uniformModel;
	bool error;
	void CompileShader(const char *vertexCode, const char *fragmentCode);
	void AddShader(unsigned int theProgram, const char *shaderCode, unsigned int shaderType);

public:

	Shader();

	void CreateFromString(const char *vertexCode, const char *fragmentCode);
	void CreateFromFiles(std::string shaderName,const char *vertexLocation, const char *fragmentLocation);
	bool good()
	{
		return !error;
	};

	unsigned int GetProjectionLocation();
	unsigned int GetModelLocation();
	unsigned int GetShaderID();
	std::string GetName()
	{
		return name;
	};
	void Use();
	void Clear();

	~Shader();



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



