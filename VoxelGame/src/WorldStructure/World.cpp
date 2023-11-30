#include "World.h"
#include "../Player.h"
#include <iostream>
#include "../GUI/GUI_Manager.h"

World::World()
{
	loadedChuncks = new std::map<std::string, Chunk *>();
	players = new std::vector<Player *>();
}

void World::AddPlayer(Player *player)
{
	(*players).push_back(player);
}

void World::PlayerUpdate(Player *player)
{
	if (player == nullptr)
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
	for (auto &chunk : *loadedChuncks)
	{
		if (chunk.second->isLoaded())
			chunk.second->Render();
	}
}

void World::loadChunk()
{

}

Chunk *World::GetChunk(glm::vec3 worldPos)
{
	glm::vec2 chunkCord = Chunk::WorldToChunkCord(worldPos);
	std::string chunkId = std::to_string(int(chunkCord.x)) + ":" + std::to_string(int(chunkCord.y));
	if (loadedChuncks->find(chunkId) != loadedChuncks->end())
		return (*loadedChuncks)[chunkId];
	return nullptr;
}

Block *World::GetBlock(glm::vec3 worldPos)
{
	Chunk *chunk = GetChunk(worldPos);
	if (chunk == nullptr)
	{
		return nullptr;
	}
	Block *block = chunk->GetBlock(worldPos);
	if (block == nullptr)
	{
		return nullptr;
	}
	return block;
}

void World::PlaceBlock(glm::vec3 worldPos, Block::BlockType type)
{
	Chunk *chunk = GetChunk(worldPos);
	if (chunk == nullptr)
	{
		return;
	}
	chunk->PlaceBlock(worldPos, type);
}

void World::RemoveBlock(glm::vec3 worldPos)
{
	Chunk *chunk = GetChunk(worldPos);
	if (chunk == nullptr)
	{
		return;
	}
	chunk->RemoveBlock(worldPos);
}

World::RaycastResult World::Raycast(glm::vec3 position, glm::vec3 direction, float maxDistance)
{
	direction = glm::normalize(direction);
	//TODO: Raycast return block result
	RaycastResult result = RaycastResult();
	Block * block = GetBlock(position);
	

	if (block != nullptr && block->GetType() != Block::BlockType::Block_Air)
	{
		result.hit = true;
		result.position = position;
		result.normal = glm::vec3(0, 0, 0);
		result.block = GetBlock(position);
		return result;
	}

	while (true)
	{
		if (Chunk::OutOfBounds(Chunk::WorldToChunkBlockPos(position)))
		{
			result.hit = false;
			result.position = position;
			result.normal = glm::vec3(0, 0, 0);
			result.block = nullptr;
			return result;
		}

		// Calculate distances to block boundaries

		float dists[Math::AXIS_COUNT];
		float min = INFINITY;
		int axis;

		for (int i = 0; i < Math::AXIS_COUNT; i++)
		{
			dists[i] = Math::DistToBlock(position, Math::Axis(i), direction);
			dists[i] *= glm::abs(1.f / direction[i]);
			if (dists[i] < min)
			{
				min = dists[i];
				axis = i;
			}
		}



		maxDistance -= min;

		if (maxDistance <= 0)
		{
			RaycastResult result;
			result.hit = false;
			return result;
		}

		position += direction * min;

		// Check for block at block boundary

		glm::ivec3 blockCoord = glm::floor(position);

		if (direction[axis] < 0.0f)
			blockCoord[axis]--;

		Block *block = GetBlock(blockCoord);

		if (block != nullptr && block->GetType() != Block::BlockType::Block_Air)
		{
			RaycastResult result;
			result.hit = true;
			result.block = block;
			result.position = position;
			result.normal = Math::AxisToNormal(Math::Axis(axis), !(direction[axis] < 0.0f));
			result.direction = Math::AxisToDir(Math::Axis(axis), !(direction[axis] < 0.0f));
			return result;
		}
	}



	



	return World::RaycastResult();
}

void World::Clear()
{
	for (auto &chunk : *loadedChuncks)
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
