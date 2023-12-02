#include "WorldManager.h"
#include "../Player.h"

//Singleton instance of WorldManager class (only one instance of WorldManager can exist)
static WorldManager *instance;
WorldManager*WorldManager::GetInstance()
{
	if (instance == nullptr)
		instance = new WorldManager();
	return instance;
}

WorldManager::WorldManager()
{}

WorldManager::~WorldManager()
{
clear();
}

//Add player to world with name worldName 
void WorldManager::AddPlayer(std::string worldName, Player *player)
{
	World *world = worlds[worldName];
	world->AddPlayer(player);
}

//Create world with name and add it to worlds map
void WorldManager::CreateWorld(std::string name)
{
	World *world = new World();
	worlds.insert(std::pair<std::string, World*>(name, world));
}

//Get world with name
World *WorldManager::GetWorld(std::string name)
{
	if(worlds.find(name) != worlds.end())
		return worlds[name];
	return nullptr;
}

//Update all worlds in worlds map with deltaTime 
void WorldManager::Update(float deltaTime)
{	
    std::map<std::string, World*>::iterator it;
    for (it = worlds.begin(); it != worlds.end(); it++)
    {
        it->second->Update(deltaTime);
    }
}

//Render all worlds in worlds map 
void WorldManager::Render()
{
	std::map<std::string, World*>::iterator it;
	for (it = worlds.begin(); it != worlds.end(); it++)
	{
		it->second->Render();
	}
}

//Clear worlds map and delete all worlds in it
void WorldManager::clear()
{
	std::map<std::string, World*>::iterator it;
	for (it = worlds.begin(); it != worlds.end(); it++)
	{
		delete(it->second);
	}
	worlds.clear();
}
