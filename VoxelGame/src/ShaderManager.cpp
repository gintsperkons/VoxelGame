#include <iostream>


#include <set>
#include "FileHandling/FileHandler.h"
#include "ShaderManager.h"
#include <GLAD/glad.h>
#include <filesystem>

static ShaderManager *instance = nullptr;
ShaderManager *ShaderManager::GetInstance()
{
	if (instance == nullptr)
		instance = new ShaderManager();
	return instance;
}


std::string ShaderManager::getShaderName(std::string vertexFileName, std::string FragmentFileName)
{
	std::string shaderNameV = std::string(vertexFileName).substr(0, std::string(vertexFileName).find("."));
	std::string shaderNameF = std::string(FragmentFileName).substr(0, std::string(FragmentFileName).find("."));
	if (shaderNameV == shaderNameF)
		return shaderNameV;
	else
	{

		if (shaderNameV == "base" || shaderNameV == "internal>file")
			return shaderNameF;
		if (shaderNameF == "base" || shaderNameF == "internal>file")
			return shaderNameV;
	}
	return shaderNameV;
}

ShaderManager::ShaderManager()
{

	//create base shader from hardcoded strings
	std::string shaderName = "base";
	Shader *shader = new Shader();
	shader->CreateBase();
	shaderList[shaderName] = shader;

	//create shaders from files
	shaderPath = std::filesystem::current_path().string() + "\\Shaders";
	std::set<std::string> allFiles;
	//get all files in shader directory
	if (FileHandler::IsDirectory(shaderPath))
	{
		for (std::string &entry : FileHandler::GetFilesInDirectory(shaderPath))
		{
			std::string fileName = entry.substr(std::string(entry).rfind("\\") + 1);
			allFiles.insert(allFiles.end(), fileName.substr(0, std::string(fileName).rfind(".")));
		}
	}
	//create shaders from files
	std::for_each(allFiles.begin(), allFiles.end(), [&](std::string shaderName)
	{
		std::string vertexFileName;
		std::string fragmentFileName;
		if (FileHandler::Exists(shaderPath + "\\" + shaderName + ".vert"))
			vertexFileName = shaderName + ".vert";
		else
			vertexFileName = "internal>file";
		if (FileHandler::Exists(shaderPath + "\\" + shaderName + ".frag"))
			fragmentFileName = shaderName + ".frag";
		else
			fragmentFileName = "internal>file";

		CreateFromFiles(vertexFileName.c_str(), fragmentFileName.c_str());
	});



}




void ShaderManager::CreateFromFiles(const char *vertexLocation, const char *fragmentLocation)
{
	//create shader from files
	std::string shaderName = getShaderName(vertexLocation, fragmentLocation);

	Shader *shader = new Shader();
	shader->CreateFromFiles(shaderName, (shaderPath + "\\" + vertexLocation).c_str(), (shaderPath + "\\" + fragmentLocation).c_str());
	if (!shader->good())
	{
		delete shader;
		return;
	}
	//if shader already exists, delete it and replace it
	if (shaderList.find(shaderName) == shaderList.end())
	{
		shaderList[shaderName] = shader;
	}
	else
	{
		delete shaderList[shaderName];
		shaderList[shaderName] = shader;
	}

}

void ShaderManager::UseShader(std::string shaderName)
{
	//if texture is already in use then return
	if (currentShader != nullptr && currentShader->GetName() == shaderName)
		return;
	//if texture is in list then use it
	if (shaderList.find(shaderName) != shaderList.end())
	{
		shaderList[shaderName]->Use();
		currentShader = shaderList[shaderName];
		return;
	}
	else
		shaderList["base"]->Use();
		currentShader = shaderList["base"];
	std::cout << "Shader not found: " << shaderName << std::endl;

}

void ShaderManager::SetMat4(std::string type, glm::mat4 *matrix)
{
	int uniformLocation = glGetUniformLocation(currentShader->GetShaderID(), type.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "Uniform not found: " << type << std::endl;
	}
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(*matrix));
}

void ShaderManager::SetUniform3(std::string type, glm::vec3 *vector)
{
	int uniformLocation = glGetUniformLocation(currentShader->GetShaderID(), type.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "Uniform not found: " << type << std::endl;
	}
	glUniform3f(uniformLocation, vector->x, vector->y, vector->z);
}

void ShaderManager::SetUniform1(std::string type, float value)
{
	int uniformLocation = glGetUniformLocation(currentShader->GetShaderID(), type.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "Uniform not found: " << type << std::endl;
	}
	glUniform1f(uniformLocation, value);
}

bool ShaderManager::uniformExists(std::string uniformName)
{
	return glGetUniformLocation(currentShader->GetShaderID(), uniformName.c_str()) < 0;
}

void ShaderManager::ClearShaderList()
{
	//delete all shaders
	for (auto it : shaderList)
	{
		it.second->Clear();
		delete(it.second);
	}
	if (currentShader != nullptr)
		currentShader->Clear();

}

ShaderManager::~ShaderManager()
{
	ClearShaderList();
}
