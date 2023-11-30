#pragma once
#include <GLM/glm.hpp>
#include <vector>
#include "../Objects/Block.h"

class Chunk
{
	std::vector<std::vector<std::vector<Block *>>> blocks;
	glm::vec2 chunkPos;
	bool loaded = false;


	void SetBlockLocal(glm::vec3 localPos, Block::BlockType type);
	std::vector<Block *> renderList;

public:
	Chunk(glm::vec2 chunkPos);
	~Chunk();

	void Init();
	void Update(float deltaTime);
	Block * GetBlock(glm::vec3 worldPos);
	void Render();
	void Clear();
	bool isLoaded()
	{
		return loaded;
	};

	void PlaceBlock(glm::vec3 worldPos, Block::BlockType type);
	void RemoveBlock(glm::vec3 worldPos);

	static bool OutOfBounds(glm::vec3 pos);
	static glm::vec3 ChunkToWorldPos(glm::vec2 chunkPos, glm::vec3 inputPos);
	static glm::vec3 WorldToChunkBlockPos(glm::vec3 inputPos);
	static glm::vec2 WorldToChunkCord(glm::vec3 inputPos);



};

