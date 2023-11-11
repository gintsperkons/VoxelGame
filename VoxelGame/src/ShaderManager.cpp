#include <iostream>


#include <set>
#include "FileHandling/FileHandler.h"
#include "ShaderManager.h"
#include <GLAD/glad.h>
#include <filesystem>



std::string ShaderManager::getShaderName(std::string vertexFileName, std::string FragmentFileName)
{
	std::string shaderNameV = std::string(vertexFileName).substr(0, std::string(vertexFileName).find("."));
	std::string shaderNameF = std::string(FragmentFileName).substr(0, std::string(FragmentFileName).find("."));
	if (shaderNameV == shaderNameF)
		return shaderNameV;
	else
	{
		if (shaderNameV == "base" || shaderNameV=="internal>file")
			return shaderNameF;
		if (shaderNameF == "base" || shaderNameF == "internal>file")
			return shaderNameV;
	}
	return shaderNameV;;
}

ShaderManager::ShaderManager()
{

	//create base shader from hardcoded strings
	std::string shaderName = "base";
	Shader *shader = new Shader();
	shader->CreateFromString(vShader, fShader);
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
			allFiles.insert(allFiles.end(),fileName.substr(0, std::string(fileName).rfind(".")));
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
			vertexFileName =  "internal>file";
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
	std::string shaderName = getShaderName(vertexLocation,fragmentLocation);
	
	Shader *shader = new Shader();
	shader->CreateFromFiles((shaderPath+"\\" + vertexLocation).c_str(), (shaderPath + "\\" + fragmentLocation).c_str());
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

void ShaderManager::ClearShaderList()
{
	//delete all shaders
	for (auto it : shaderList)
	{
		it.second->ClearShader();
		delete(it.second);
	}

}

ShaderManager::~ShaderManager()
{
	ClearShaderList();
}
