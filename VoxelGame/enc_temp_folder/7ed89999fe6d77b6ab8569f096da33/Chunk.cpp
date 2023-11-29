#include "Chunk.h"
#include <cmath>
#include <iostream>
#include "Generator/TerrainGenerator.h"




int CHUNK_SIZE = 16;
int WORLD_HIGH = 256;

void Chunk::SetBlockLocal(glm::vec3 localPos, Block::BlockType type)
{
	blocks[localPos.y][localPos.x][localPos.z]->ChangeType(type);
	renderList.push_back(blocks[localPos.y][localPos.x][localPos.z]);

}

Chunk::Chunk(glm::vec2 chunkPos)
{
	this->chunkPos = chunkPos;
	std::vector<std::vector<std::vector<Block *> > > temp(
		WORLD_HIGH, std::vector<std::vector<Block *> >(
		CHUNK_SIZE, std::vector<Block *>(CHUNK_SIZE)));
	blocks = temp;

	


	for (int y = 0; y < WORLD_HIGH; y++)
	{
		for (int x = 0; x < CHUNK_SIZE; x++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{	
				blocks[y][x][z] = new Block();
				blocks[y][x][z]->Create(ChunkToWorldPos(chunkPos, glm::vec3(x, y, z)), "air");
			}
		}
	}
	
}

Chunk::~Chunk()
{
	Clear();
}

void Chunk::Init()
{
	std::cout	 << "Chunk Init" << std::endl;

	glm::vec3 chunkStart = ChunkToWorldPos(chunkPos, glm::vec3(0, 0, 0));
	std::vector<std::vector<float>> result = TerrainGenerator::GetInstance()->GenerateChunkSurface(chunkStart.x, chunkStart.z, CHUNK_SIZE, CHUNK_SIZE, 0);
	
	
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

void Chunk::Update(float deltaTime)
{
	
}

Block* Chunk::GetBlock(glm::vec3 worldPos)
{
	if (worldPos.y < 0 || worldPos.y > WORLD_HIGH)
	{
		return nullptr;
	}

	glm::ivec3 chunkPos = WorldToChunkBlockPos(worldPos);
	return blocks[chunkPos.y][chunkPos.x][chunkPos.z];
}

void Chunk::Render()
{
	for (Block* b : renderList)
	{
		b->Render();
	}
}

glm::vec2 Chunk::WorldToChunkCord(glm::vec3 inputPos)
{
	glm::vec2 chunckCord = glm::vec3();
	chunckCord.x = floor(inputPos.x / CHUNK_SIZE);
	chunckCord.y = floor(inputPos.z / CHUNK_SIZE);
	return chunckCord;
}

glm::vec3 Chunk::ChunkToWorldPos(glm::vec2 chunkPos, glm::vec3 localPos)
{
	glm::vec3 resultPos = glm::vec3();
	resultPos.x = floor(localPos.x +( chunkPos.x * CHUNK_SIZE));
	resultPos.y = localPos.y;
	resultPos.z = floor(localPos.z + (chunkPos.y * CHUNK_SIZE));
	return resultPos;
}

glm::vec3 Chunk::WorldToChunkBlockPos(glm::vec3 worldPos)
{
	glm::vec2 chunkCord = WorldToChunkCord(worldPos);
	glm::vec3 localPos = glm::vec3();
	float inChunkPosX =((int)floor(worldPos.x) % CHUNK_SIZE);
	float inChunkPosZ = ((int)floor(worldPos.z) % CHUNK_SIZE);
	float ChunkPosX = chunkCord.x * CHUNK_SIZE;
	float ChunkPosZ = chunkCord.y * CHUNK_SIZE;
	localPos.x =  inChunkPosX - ChunkPosX -1;
	localPos.y = floor(worldPos.y);
	localPos.z = inChunkPosZ - ChunkPosZ -1;
	if (OutOfBounds(localPos))
	{
 		return localPos;
	}
	return localPos;
}
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
