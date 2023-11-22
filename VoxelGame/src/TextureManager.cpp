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
	CreateTexture("default.jpg");

	//get all files in shader directory
	if (FileHandler::IsDirectory(texturePath))
	{
		for (std::string &entry : FileHandler::GetFilesInDirectory(texturePath))
		{
			std::string fileName = entry.substr(std::string(entry).rfind("\\") + 1);
			CreateTexture(fileName);
		}
	}

}

void TextureManager::CreateTexture(std::string fileName)
{
	//creates texture and if successful then ad to list
	std::string textureName = std::string(fileName).substr(0, std::string(fileName).find("."));
	Texture *tempTexture = new Texture();
	tempTexture->Create(texturePath + "\\" + fileName, textureName);
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
	if (currentTexture!= nullptr && currentTexture->GetName() == textureName)
		return;
	//if texture is in list then use it
	if (textureList.find(textureName) != textureList.end())
	{
		textureList[textureName]->Use();
		currentTexture = textureList[textureName];
		return;
	}
		std::cout << "Texture not found: " << textureName << std::endl;
		
}

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
