#include "Chunk.h"
#include <cmath>
#include <iostream>
#include "Generator/TerrainGenerator.h"



//chunk static variables
int CHUNK_SIZE = 16;
int WORLD_HIGH = 256;

//sets the block at the local position to the type given
void Chunk::SetBlockLocal(glm::vec3 localPos, Block::BlockType type)
{
	blocks[localPos.y][localPos.x][localPos.z]->ChangeType(type);
	if (type == Block::BlockType::Block_Air)
		return;
	//if the block is not air add it to the render list
	renderList.push_back(blocks[localPos.y][localPos.x][localPos.z]);

}


Chunk::Chunk(glm::vec2 chunkPos)
{
	//creates a 3d array of blocks with the size of the world high and chunk size
	this->chunkPos = chunkPos;
	std::vector<std::vector<std::vector<Block *> > > temp(
		WORLD_HIGH, std::vector<std::vector<Block *> >(
		CHUNK_SIZE, std::vector<Block *>(CHUNK_SIZE)));
	blocks = temp;

	//sets all the blocks to air
	for (int y = 0; y < WORLD_HIGH; y++)
	{
		for (int x = 0; x < CHUNK_SIZE; x++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				blocks[y][x][z] = new Block();
				blocks[y][x][z]->Create(ChunkToWorldPos(chunkPos, glm::vec3(x, y, z)), Block::BlockType::Block_Air);
			}
		}
	}

}

Chunk::~Chunk()
{
	Clear();
}

//generates the chunk using the terrain generator
void Chunk::Init()
{
	//chunk start is the position of the chunk in the world
	glm::vec3 chunkStart = ChunkToWorldPos(chunkPos, glm::vec3(0, 0, 0));
	std::vector<std::vector<float>> result = TerrainGenerator::GetInstance()->GenerateChunkSurface(chunkStart.x, chunkStart.z, CHUNK_SIZE, CHUNK_SIZE, 0);

	//sets stone blocks to the height of the surface given by the terrain generator
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			int y = abs(round(result[z][x]));

			SetBlockLocal(glm::vec3(x, y, z), Block::BlockType::Block_Stone);
		}
	}
	loaded = true;
}

//clears the chunk of all blocks and deletes them from memory
void Chunk::Clear()
{
	for (int y = 0; y < WORLD_HIGH; y++)
	{
		for (int x = 0; x < CHUNK_SIZE; x++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				delete blocks[y][x][z];
			}
		}
	}
}

//updates the chunk activities (not used for now) 
void Chunk::Update(float deltaTime)
{}

//gets the block at the world position given
Block *Chunk::GetBlock(glm::vec3 worldPos)
{
	//if the block is out of bounds return null
	if (OutOfBounds(WorldToChunkBlockPos(worldPos)))
		return nullptr;

	//otherwise the block pointer at the position
	glm::ivec3 chunkPos = WorldToChunkBlockPos(worldPos);
	return blocks[chunkPos.y][chunkPos.x][chunkPos.z];
}

//renders all the blocks in the chunk render list 
void Chunk::Render()
{
	for (Block *b : renderList)
	{
		//if the block is air remove it from the render list
		if (b->GetType() == Block::BlockType::Block_Air)
		{
			//get index of block to remove
			auto i = std::find(renderList.begin(), renderList.end(), b);
			if (i != renderList.end())
				renderList.erase(i);
		}
		b->Render();
	}
}

//converts world position to chunk position of chunk coordinates
glm::vec2 Chunk::WorldToChunkCord(glm::vec3 worldPos)
{
	glm::vec2 chunckCord = glm::vec3();
	chunckCord.x = floor(worldPos.x / CHUNK_SIZE);
	chunckCord.y = floor(worldPos.z / CHUNK_SIZE);
	return chunckCord;
}

//converts chunk position to world position
glm::vec3 Chunk::ChunkToWorldPos(glm::vec2 chunkPos, glm::vec3 localPos)
{
	glm::vec3 resultPos = glm::vec3();
	resultPos.x = floor(localPos.x + (chunkPos.x * CHUNK_SIZE));
	resultPos.y = localPos.y;
	resultPos.z = floor(localPos.z + (chunkPos.y * CHUNK_SIZE));
	return resultPos;
}

//converts world position to chunk position of block coordinates in chunk
glm::vec3 Chunk::WorldToChunkBlockPos(glm::vec3 worldPos)
{
	float ChunkPosX = floor(worldPos.x / CHUNK_SIZE);
	float ChunkPosZ = floor(worldPos.z / CHUNK_SIZE);

	glm::vec3 localPos = glm::vec3();
	localPos.x = floor(worldPos.x - (ChunkPosX * CHUNK_SIZE));
	localPos.y = floor(worldPos.y);
	localPos.z = floor(worldPos.z - (ChunkPosZ * CHUNK_SIZE));

	if (OutOfBounds(localPos))
	{
		return glm::vec3(0, 0, 0);
	}

	return localPos;
}

//places a block at the world position given if position is out of bounds do nothing
void Chunk::PlaceBlock(glm::vec3 worldPos, Block::BlockType type)
{
	glm::vec3 localPos = WorldToChunkBlockPos(worldPos);
	if (OutOfBounds(localPos))
		return;
	SetBlockLocal(localPos, type);
	return;
}


//removes a block at the world position given if position is out of bounds do nothing
void Chunk::RemoveBlock(glm::vec3 worldPos)
{
	glm::vec3 localPos = WorldToChunkBlockPos(worldPos);
	if (OutOfBounds(localPos))
		return;
	Block *b = blocks[localPos.y][localPos.x][localPos.z];
	if (b->GetType() == Block::BlockType::Block_Air)
		return;

	//remove block from render list if it is in it
	auto i = std::find(renderList.begin(), renderList.end(), b);
	if (i != renderList.end())
		renderList.erase(i);

	SetBlockLocal(localPos, Block::BlockType::Block_Air);
	return;
}

//sets the chunk to unloaded to not render it
void Chunk::Unload()
{
	loaded = false;
}

//sets the chunk to loaded to render it
void Chunk::Load()
{
	loaded = true;
}

//checks if the chunk is in the render distance from the center chunk (players chunk)
bool Chunk::InRenderDistance(glm::vec2 centerChunkCords, int renderDistance)
{
	if ((chunkPos.x <= centerChunkCords.x + renderDistance && chunkPos.x >= centerChunkCords.x - renderDistance)
		&&
		(chunkPos.y <= centerChunkCords.y + renderDistance && chunkPos.y >= centerChunkCords.y - renderDistance))
	{
		return true;
	}
	return false;
}

//checks if the position is out of bounds of the chunk
bool Chunk::OutOfBounds(glm::vec3 pos)
{
	if (pos.x >= CHUNK_SIZE || pos.x < 0)
		return true;
	if (pos.y >= WORLD_HIGH || pos.y < 0)
		return true;
	if (pos.z >= CHUNK_SIZE || pos.z < 0)
		return true;

	return false;
}
