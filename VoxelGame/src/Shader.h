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

	void CreateBase();
	void CreateFromFiles(std::string shaderName,const char *vertexLocation, const char *fragmentLocation);
	bool good()
	{
		return !error;
	};

	unsigned int GetProjectionLocation();
	unsigned int GetModelLocation();
	unsigned int GetShaderID();
	std::string GetName();
	void Use();
	void Clear();

	~Shader();



private:
	//Base shader for if no file found
// Vertex Shader
	const char *vShader = "                                                \n\
#version 330 core                                               \n\
layout(location = 0) in vec3 aPos;                                               \n\
	layout(location = 1) in vec3 aColor;                                               \n\
	layout(location = 2) in vec2 aTexCoord;                                               \n\
                                               \n\
	out vec3 ourColor;                                               \n\
	out vec2 TexCoord;                                               \n\
                                               \n\
	uniform mat4 model;                                               \n\
	uniform mat4 view;                                               \n\
	uniform mat4 projection;                                               \n\
		\n\
	void main()                                               \n\
	{                                               \n\
		gl_Position = projection * view * model * vec4(aPos, 1.0f);                                               \n\
		ourColor = aColor;                                               \n\
		TexCoord = aTexCoord;                                               \n\
	}";

// Fragment Shader
	const char *fShader = "                                                \n\
#version 330 core														\n\
out vec4 FragColor;														\n\
														\n\
	in vec3 ourColor;														\n\
	in vec2 TexCoord;														\n\
														\n\
	uniform sampler2D ourTexture;														\n\
														\n\
	void main()														\n\
	{														\n\
		FragColor = texture(ourTexture, TexCoord);														\n\
	} ";														
};



