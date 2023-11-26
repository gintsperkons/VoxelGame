#pragma once
#include <vector>
#include "Chunk.h"
#include "../Player.h"

class Player;

class World
{
std::map<std::string,Chunk*> *loadedChuncks;
std::vector<Player*> *players;
public:
	World();
	void AddPlayer(Player* player);
	void PlayerUpdate(Player *player);
	void Update(float deltaTime);
	void Render();
	void loadChunk();
	void Clear();
	~World();
};

