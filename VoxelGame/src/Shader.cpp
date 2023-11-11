#include "Shader.h"
#include "FileHandling/FileHandler.h"
#include <GLAD/glad.h>

void Shader::CompileShader(const char *vertexCode, const char *fragmentCode)
{
	shaderID = glCreateProgram();

	if (!shaderID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	int result = 0;
	char eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		error = true;
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		error = true;
		return;
	}

	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformModel = glGetUniformLocation(shaderID, "model");
}

void Shader::AddShader(unsigned int theProgram, const char *shaderCode, unsigned int shaderType)
{
	unsigned int theShader = glCreateShader(shaderType);

	const char *theCode[1];
	theCode[0] = shaderCode;

	int codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		error = true;
		return;
	}

	glAttachShader(theProgram, theShader);
}

Shader::Shader()
{
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
	error = false;
}


void Shader::CreateFromString(const char *vertexCode, const char *fragmentCode)
{
	CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char *vertexLocation, const char *fragmentLocation)
{
	std::string vertexString;
	std::string fragmentString;
	if (std::string(vertexLocation).find("internal>file") == std::string::npos)
		vertexString = FileHandler::ReadFile(vertexLocation);
	else
		vertexString = vShader;
	if (std::string(fragmentLocation).find("internal>file") == std::string::npos)
		fragmentString = FileHandler::ReadFile(fragmentLocation);
	else
		fragmentString = fShader;
	CompileShader(vertexString.c_str(), fragmentString.c_str());
}

unsigned int Shader::GetProjectionLocation()
{
	return uniformProjection;
}

unsigned int Shader::GetModelLocation()
{
	return uniformModel;
}

unsigned int Shader::GetShaderID()
{
	return shaderID;
}

void Shader::UseShader()
{
	glUseProgram(shaderID);
}

void Shader::ClearShader()
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
	ClearShader();
}
