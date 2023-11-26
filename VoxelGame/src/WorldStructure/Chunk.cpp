#include "Chunk.h"
#include <cmath>
#include <iostream>
#include "Generator/TerrainGenerator.h"




int CHUNK_SIZE = 16;
int WORLD_HIGH = 256;

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
			int y = abs(round(result[x][z]));

			blocks[y][z][x]->ChangeType("stone");
			/*for (; y >= 0; y--)
			{
				blocks[y][x][z]->ChangeType("stone");
			}*/
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

	glm::vec3 chunkPos = WorldToChunkBlockPos(worldPos);
	return blocks[chunkPos.y][chunkPos.x][chunkPos.z];
}

void Chunk::Render()
{
for (int y = 0; y < WORLD_HIGH; y++)
	{
		for (int x = 0; x < CHUNK_SIZE; x++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				if (blocks[y][x][z]->GetType() == "stone")
				{
					blocks[y][x][z]->Render();
				}

			}
		}
	}
}

glm::vec3 Chunk::WorldToChunkPos(glm::vec3 inputPos)
{
	glm::vec3 resultPos = glm::vec3();
	resultPos.x = floor(inputPos.x / CHUNK_SIZE);
	resultPos.y = inputPos.y;
	resultPos.z = floor(inputPos.z / CHUNK_SIZE);
	return resultPos;
}

glm::vec3 Chunk::ChunkToWorldPos(glm::vec2 chunkPos, glm::vec3 inputPos)
{
	glm::vec3 resultPos = glm::vec3();
	resultPos.x = floor(inputPos.x +( chunkPos.x * CHUNK_SIZE));
	resultPos.y = inputPos.y;
	resultPos.z = floor(inputPos.z + (chunkPos.y * CHUNK_SIZE));
	return resultPos;
}

glm::vec3 Chunk::WorldToChunkBlockPos(glm::vec3 inputPos)
{
	glm::vec3 resultPos = glm::vec3();
	resultPos.x = abs(floor(inputPos.x / CHUNK_SIZE));
	resultPos.y = inputPos.y;
	resultPos.z = abs(floor(inputPos.z / CHUNK_SIZE));
	return resultPos;
}

