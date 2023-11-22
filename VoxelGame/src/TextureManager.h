#pragma once
#include <string>
#include <map>
#include "Texture.h"



class TextureManager
{
	std::string texturePath;
	Texture* currentTexture;

public:
	std::map<std::string, Texture*> textureList;
	TextureManager();

void CreateTexture(std::string fileName);
void UseTexture(std::string textureName);
void SetSkyMapTexture();
void ClearTextureList();

~TextureManager();


static TextureManager *GetInstance();

};

