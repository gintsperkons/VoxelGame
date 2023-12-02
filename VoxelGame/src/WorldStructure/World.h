#pragma once
#include "../Math.h"
#include <vector>
#include "Chunk.h"
#include "../Player.h"

class Player;

class World
{
std::map<std::string,Chunk*> *loadedChuncks;
std::vector<Player*> *players;
public:
	struct RaycastResult {
		bool hit;
		glm::vec3 position;
		glm::vec3 normal;
		Math::Direction direction;
		Block *block;
	};

	World();
	void AddPlayer(Player* player);
	void PlayerUpdate(Player *player);
	void Update(float deltaTime);
	void Render();
	Chunk * GetChunk(glm::vec3 worldPos);
	Block *GetBlock(glm::vec3 worldPos);
	void PlaceBlock(glm::vec3 worldPos, Block::BlockType type);
	void RemoveBlock(glm::vec3 worldPos);
	World::RaycastResult Raycast(glm::vec3 position, glm::vec3 direction, float maxDistance);
	void Clear();
	~World();
};

