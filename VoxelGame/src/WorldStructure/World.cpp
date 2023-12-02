#include "World.h"
#include "../Player.h"
#include "../GUI/GUI_Manager.h"

World::World()
{
	loadedChuncks = new std::map<std::string, Chunk *>();
	players = new std::vector<Player *>();
}

// add player to world
void World::AddPlayer(Player *player)
{
	(*players).push_back(player);
}

// update player position and render distance and load chunks around player and unload chunks that are not in render distance
void World::PlayerUpdate(Player *player)
{
	if (player == nullptr)
		return;
	
	//get player render distance and position and player chunk position
	int playerRenderDistance = player->getRenderDistance();
	glm::vec3 playerPos = player->getPosition();
	glm::vec2 centerChunkCord = Chunk::WorldToChunkCord(playerPos);

	//create chunk id for player chunk (x:y)
	std::string chunkId = std::to_string(int(centerChunkCord.x)) + ":" + std::to_string(int(centerChunkCord.y));

	//if player chunk is not loaded create new chunk and load it
	if (loadedChuncks->find(chunkId) == loadedChuncks->end())
	{
		(*loadedChuncks)[chunkId] = new Chunk(glm::vec2(centerChunkCord.x, centerChunkCord.y));
		(*loadedChuncks)[chunkId]->Init();
	}

	//load chunks around player chunk from -render distance to +render distance in x and z axis
	for (int x = -playerRenderDistance; x <= playerRenderDistance; x++)
	{
		for (int z = -playerRenderDistance; z <= playerRenderDistance; z++)
		{
			glm::vec2 chunkCord = glm::vec2(centerChunkCord.x + x, centerChunkCord.y + z);
			std::string chunkId = std::to_string(int(chunkCord.x)) + ":" + std::to_string(int(chunkCord.y));
			if (loadedChuncks->find(chunkId) == loadedChuncks->end())
			{
				(*loadedChuncks)[chunkId] = new Chunk(glm::vec2(chunkCord.x, chunkCord.y));
				(*loadedChuncks)[chunkId]->Init();
			}
		}
	}

	//chunk ids to remove
	std::vector<std::string> toRemove;

	//check if chunks are in render distance and if they are not unload them and add them to remove list
	for (auto &chunk : *loadedChuncks)
	{
		//if chunk is not in render distance unload it and add it to remove list
		if (!chunk.second->InRenderDistance(centerChunkCord,playerRenderDistance))
		{
			chunk.second->Unload();
			toRemove.push_back(chunk.first);
		}
		else
		{
			//if chunk is in render distance remove it from remove list and load it
			auto i = std::find(toRemove.begin(), toRemove.end(), chunk.first);
			if (i != toRemove.end())
			{
				
				toRemove.erase(i);

			}
			chunk.second->Load();
		}
	}

	//remove chunks from that are in remove list from loaded chunks and delete them (form now later maybe save to file to not loose progress)
	for (auto &chunk : toRemove)
	{
		if (loadedChuncks->find(chunkId) != loadedChuncks->end())
		{
			delete (*loadedChuncks)[chunk];
			loadedChuncks->erase(chunk);
		}
		
	}
}

//update loaded chunks 
void World::Update(float deltaTime)
{
	for (auto &chunk : *loadedChuncks)
	{
		chunk.second->Update(deltaTime);
	}
}

//render loaded chunks if they are loaded/ready to render
void World::Render()
{
	for (auto &chunk : *loadedChuncks)
	{
		if (chunk.second->isLoaded())
			chunk.second->Render();
	}
}

//get chunk at world position
Chunk *World::GetChunk(glm::vec3 worldPos)
{
	//get chunk coordinates from world position and create chunk id (x:y) and if in loaded chunks return chunk
	glm::vec2 chunkCord = Chunk::WorldToChunkCord(worldPos);
	std::string chunkId = std::to_string(int(chunkCord.x)) + ":" + std::to_string(int(chunkCord.y));
	if (loadedChuncks->find(chunkId) != loadedChuncks->end())
		return (*loadedChuncks)[chunkId];
	return nullptr;
}

//get block at world position
Block *World::GetBlock(glm::vec3 worldPos)
{	
	//get chunk at world position and if chunk is null return null
	Chunk *chunk = GetChunk(worldPos);
	if (chunk == nullptr)
	{
		return nullptr;
	}
	//get block at world position from chunk and if block is null return null
	Block *block = chunk->GetBlock(worldPos);
	if (block == nullptr)
	{
		return nullptr;
	}
	return block;
}

//place block at world position if chunk is not null
void World::PlaceBlock(glm::vec3 worldPos, Block::BlockType type)
{
	Chunk *chunk = GetChunk(worldPos);
	if (chunk == nullptr)
	{
		return;
	}
	chunk->PlaceBlock(worldPos, type);
}

//remove block at world position if chunk is not null
void World::RemoveBlock(glm::vec3 worldPos)
{
	Chunk *chunk = GetChunk(worldPos);
	if (chunk == nullptr)
	{
		return;
	}
	chunk->RemoveBlock(worldPos);
}

//raycast from position in direction with max distance and return raycast result 
World::RaycastResult World::Raycast(glm::vec3 position, glm::vec3 direction, float maxDistance)
{
	direction = glm::normalize(direction);
	//TODO: Raycast return block result
	RaycastResult result = RaycastResult();
	Block * block = GetBlock(position);
	
	//if player in block thats not air return block hit result
	if (block != nullptr && block->GetType() != Block::BlockType::Block_Air)
	{
		result.hit = true;
		result.position = position;
		result.normal = glm::vec3(0, 0, 0);
		result.block = GetBlock(position);
		return result;
	}

	//raycast loop
	while (true)
	{	
		//if position is out of bounds return raycast result with hit false
		if (Chunk::OutOfBounds(Chunk::WorldToChunkBlockPos(position)))
		{
			result.hit = false;
			result.position = position;
			result.normal = glm::vec3(0, 0, 0);
			result.block = nullptr;
			return result;
		}

		// Calculate distances to next block boundaries
		float dists[Math::AXIS_COUNT];
		float min = INFINITY;
		int axis;

		// Find nearest block boundary
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

		// Check if raycast is finished
		maxDistance -= min;
		if (maxDistance <= 0)
		{
			RaycastResult result;
			result.hit = false;
			return result;
		}

		// Advance raycast to next block boundary
		position += direction * min;

		// Check for block at block boundary

		glm::ivec3 blockCoord = glm::floor(position);

		if (direction[axis] < 0.0f)
			blockCoord[axis]--;

		Block *block = GetBlock(blockCoord);
		//if block is not air return raycast result with hit true and block data
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

	// if no block hit return raycast result with hit false
	return World::RaycastResult();
}

//clear all loaded chunks and memory allocated for them and players
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
