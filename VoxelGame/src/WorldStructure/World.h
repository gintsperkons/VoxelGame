#pragma once
#include <vector>
#include "Chunk.h"
#include "../Player.h"

class World
{
std::map<std::string,Chunk*> loadedChuncks;
std::vector<Player*> players;
public:
	World();
	void AddPlayer(Player* player);
	void Update(float deltaTime);
	void Render();
	void loadChunk();
	void Clear();
	~World();
};

