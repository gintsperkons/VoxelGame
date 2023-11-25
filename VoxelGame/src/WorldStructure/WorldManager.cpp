#include "WorldManager.h"
#include <iostream>
#include "../Player.h"

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

void WorldManager::AddPlayer(std::string worldName, Player *player)
{
	World *world = worlds[worldName];
	world->AddPlayer(player);
}

void WorldManager::CreateWorld(std::string name)
{
	World *world = new World();
	worlds.insert(std::pair<std::string, World*>(name, world));
}

World *WorldManager::GetWorld(std::string name)
{
	return nullptr;
}

void WorldManager::UnloadWorld(std::string name)
{}

void WorldManager::Update(float deltaTime)
{	
    std::map<std::string, World*>::iterator it;
    for (it = worlds.begin(); it != worlds.end(); it++)
    {
        it->second->Update(deltaTime);
    }
}

void WorldManager::Render()
{
	std::map<std::string, World*>::iterator it;
	for (it = worlds.begin(); it != worlds.end(); it++)
	{
		it->second->Render();
	}
}

void WorldManager::clear()
{
	std::map<std::string, World*>::iterator it;
	for (it = worlds.begin(); it != worlds.end(); it++)
	{
		delete(it->second);
	}
	worlds.clear();
}
