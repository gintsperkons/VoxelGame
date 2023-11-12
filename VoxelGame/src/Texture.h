#pragma once
#include <string>

class Texture
{
	std::string name;
	unsigned int texture;
	int width, height, nrChannels;
	bool error;
public:
	Texture();
	void Create(std::string imagePath, std::string textureName);
	void Use();
	std::string GetName()
	{
		return name;
	}
	bool good()
	{
		return !error;
	}
	void Clear();
	~Texture();
};

