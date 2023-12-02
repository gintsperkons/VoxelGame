#include <GLAD/glad.h>
#include <filesystem>
#include <iostream>
#include <set>
#include "TextureManager.h"
#include "FileHandling/FileHandler.h"

static TextureManager* instance = nullptr;
TextureManager *TextureManager::GetInstance()
{
	if (instance == nullptr)
		instance = new TextureManager();
	return instance;
}


TextureManager::TextureManager()
{
	//get path to textures folder and create default texture
	texturePath = std::filesystem::current_path().string() + "\\Textures";
	currentTexture = nullptr;
	CreateTexture("default.png");

	//get all files in shader directory
	if (FileHandler::IsDirectory(texturePath))
	{
		for (std::string &entry : FileHandler::GetFilesInDirectory(texturePath))
		{
			if (FileHandler::IsDirectory(entry))
				continue;
			std::string fileName = entry.substr(std::string(entry).rfind("\\") + 1);
			CreateTexture(fileName);
		}
	}

}

//creates a texture from a file
void TextureManager::CreateTexture(std::string fileName)
{
	//creates texture and if successful then ad to list
	std::string textureName = std::string(fileName).substr(0, std::string(fileName).find("."));
	Texture *tempTexture = new Texture();
		tempTexture->Create(texturePath + "\\" + fileName, textureName, GL_TEXTURE_2D);
	if (tempTexture->good())
	//if shader already exists, delete it and replace it
		if (textureList.find(textureName) == textureList.end())
			textureList[textureName] = tempTexture;
		else
		{
			delete textureList[textureName];
			textureList[textureName] = tempTexture;
		}
	else
		delete tempTexture;
	

}



void TextureManager::UseTexture(std::string textureName)
{	
	//if texture is already in use then return
	if (currentTexture != nullptr && currentTexture->GetName() == textureName)
	{
		textureList[textureName]->Use();
		return;
	}
	//if texture is in list then use it
	if (textureList.find(textureName) != textureList.end())
	{
		textureList[textureName]->Use();
		currentTexture = textureList[textureName];
		return;
	}
	//if default texture exists then use it
	if (textureList.find("default") != textureList.end())
	{
		textureList["default"]->Use();
		currentTexture = textureList["default"];
		return;
	}

		std::cout << "Texture not found: " << textureName << std::endl;
		
}

//clears all textures
void TextureManager::ClearTextureList()
{
	//delete all textures
	for (auto it : textureList)
	{
		it.second->Clear();
		delete(it.second);
	}
	if (currentTexture != nullptr)
		currentTexture->Clear();
}

TextureManager::~TextureManager()
{
	ClearTextureList();
}
