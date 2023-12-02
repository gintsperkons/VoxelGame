#include "Shader.h"
#include "FileHandling/FileHandler.h"
#include <GLAD/glad.h>
#include <iostream>

// compile shader 
void Shader::CompileShader(const char *vertexCode, const char *fragmentCode)
{
	shaderID = glCreateProgram();

	// check if shader program wasn't created return error
	if (!shaderID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	// add shaders to shader program and compile them 
	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);


	int result = 0;
	char eLog[1024] = { 0 };

	// link shader program and check for errors
	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		error = true;
		return;
	}

	// validate shader program and check for errors
	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		error = true;
		return;
	}

	// get uniform locations
	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformModel = glGetUniformLocation(shaderID, "model");
}

// add shader to shader program
void Shader::AddShader(unsigned int theProgram, const char *shaderCode, unsigned int shaderType)
{
	// create shader
	unsigned int theShader = glCreateShader(shaderType);

	const char *theCode[1];
	theCode[0] = shaderCode;

	int codeLength[1];
	codeLength[0] = strlen(shaderCode);

	//create shader and compile it from source
	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	// check for errors
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		error = true;
		return;
	}

	// attach shader to shader program
	glAttachShader(theProgram, theShader);
}

Shader::Shader()
{
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
	error = false;
}


std::string Shader::GetName()
{
	return name;
}

void Shader::CreateBase()
{
	CompileShader(vShader, fShader);
}

// create shader from files 
void Shader::CreateFromFiles(std::string shaderName,const char *vertexLocation, const char *fragmentLocation)
{	
	this->name = shaderName;
	std::string vertexString;
	std::string fragmentString;
	// if vertexLocation or fragmentLocation is not a file path, use the string as the shader code from header file as default
	if (std::string(vertexLocation).find("internal>file") == std::string::npos)
		vertexString = FileHandler::ReadFile(vertexLocation);
	else
		vertexString = vShader;
	if (std::string(fragmentLocation).find("internal>file") == std::string::npos)
		fragmentString = FileHandler::ReadFile(fragmentLocation);
	else
		fragmentString = fShader;
	// compile shader 
	CompileShader(vertexString.c_str(), fragmentString.c_str());
}

// get uniform location projection
unsigned int Shader::GetProjectionLocation()
{
	return uniformProjection;
}

//get uniform location model
unsigned int Shader::GetModelLocation()
{
	return uniformModel;
}

//get shader id
unsigned int Shader::GetShaderID()
{
	return shaderID;
}

// use shader
void Shader::Use()
{
	glUseProgram(shaderID);
}

// clear shader from memory
void Shader::Clear()
{
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;
}

Shader::~Shader()
{
	Clear();
}
