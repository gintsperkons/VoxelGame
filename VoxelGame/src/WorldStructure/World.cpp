#include "World.h"
#include "../Player.h"
#include <iostream>

World::World()
{
loadedChuncks = new std::map<std::string, Chunk*>();
players = new std::vector<Player*>();
}

void World::AddPlayer(Player * player)
{
	(*players).push_back(player);
}

void World::PlayerUpdate(Player * player)
{
	if(player == nullptr)
		return;


	int playerRenderDistance = player->getRenderDistance();
	glm::vec3 playerPos = player->getPosition();
	glm::vec2 centerChunkCord = Chunk::WorldToChunkCord(playerPos);

	std::string chunkId = std::to_string(int(centerChunkCord.x)) + ":" + std::to_string(int(centerChunkCord.y));


	if (loadedChuncks->find(chunkId) == loadedChuncks->end())
	{

		(*loadedChuncks)[chunkId] = new Chunk(glm::vec2(centerChunkCord.x, centerChunkCord.y));
		(*loadedChuncks)[chunkId]->Init();
	}


	for (auto &chunk : *loadedChuncks)
	{
		//std::cout << chunk.first << std::endl;
	}

	//test block Getter 
	if (loadedChuncks->find(chunkId) != loadedChuncks->end())
	{
		Block *block = (*loadedChuncks)[chunkId]->GetBlock(player->getPosition());
		if (block != nullptr)
		{
			//std::cout << block->GetType() << std::endl;
		}
	}
}

void World::Update(float deltaTime)
{	
	for (auto &chunk : *loadedChuncks)
	{
		chunk.second->Update(deltaTime);
	}
}

void World::Render()
{
	for (auto& chunk : *loadedChuncks)
	{
		if (chunk.second->isLoaded())
		chunk.second->Render();
	}
}

void World::loadChunk()
{
	
}

void World::GetBlock(glm::vec3 worldPos)
{
	//TODO: get block
}

World::RaycastResult World::Raycast(glm::vec3 position, glm::vec3 direction, float maxDistance)
{
	direction = glm::normalize(direction);
	//TODO: Raycast return block result
	RaycastResult result;

	return World::RaycastResult();
}

void World::Clear()
{
	for (auto& chunk : *loadedChuncks)
	{
		delete chunk.second;
	}
	loadedChuncks->clear();
	delete(loadedChuncks);
	delete(players);

}

World::~World()
{
	Clear();
}