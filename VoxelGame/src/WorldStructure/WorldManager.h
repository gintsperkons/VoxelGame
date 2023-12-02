#pragma once
#include <map>
#include <string>
#include "World.h"
class WorldManager
{
std::map<std::string, World*> worlds;
public:
	WorldManager();
	~WorldManager();
	void AddPlayer(std::string worldName, Player* player);
	void CreateWorld(std::string name);
	World* GetWorld(std::string name);
	void Update(float deltaTime);
	void Render();
	void clear();

	static WorldManager* GetInstance();
};

