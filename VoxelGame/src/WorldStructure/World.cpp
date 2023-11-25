#include "World.h"
#include "../Player.h"
#include <iostream>

World::World()
{}

void World::AddPlayer(Player * player)
{
	players.push_back(player);
}

void World::Update(float deltaTime)
{	
	for (auto &player : players)
	{
		int playerRenderDistance = player->getRenderDistance();
		glm::vec3 playerPos = player->getPosition();
		glm::vec3 centerChunk = Chunk::WorldToChunkPos(playerPos);
		//loadedChunk has chunk "1:1"
		//if chunk not  loadedChunk map create new
//if chunk not in render distance delete
		std::string chunkId = std::to_string(int(centerChunk.x)) + ":" + std::to_string(int(centerChunk.z));
		if (loadedChuncks.find(chunkId) == loadedChuncks.end())
		{
			loadedChuncks[chunkId] = new Chunk(glm::vec2(centerChunk.x, centerChunk.z));
			loadedChuncks[chunkId]->Init();
		}


		//test block Getter 
		if (loadedChuncks.find(chunkId) != loadedChuncks.end())
		{
			Block *block = loadedChuncks[chunkId]->GetBlock(player->getPosition());
			if (block != nullptr){
			}
		}
	}

	for (auto &chunk : loadedChuncks)
	{
		chunk.second->Update(deltaTime);
	}
}

void World::Render()
{
	for (auto& chunk : loadedChuncks)
	{
		if (chunk.second->isLoaded())
		chunk.second->Render();
	}
}

void World::loadChunk()
{
	
}

void World::Clear()
{
	for (auto& chunk : loadedChuncks)
	{
		delete chunk.second;
	}
	loadedChuncks.clear();
}

World::~World()
{
	Clear();
}
