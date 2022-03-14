#pragma once
#include <vector>
#include "Block.h"
#include "Coords.h"

class Player;

class Level
{
public:
	Level();
	Level(SDL_Rect src, float scale, float offsetX, float offsetY);
	~Level();

	void draw();
	void update(bool& running, int& savedKills, Player& player);

	std::vector<Block> blocks;
private:
	int killCount = 0;
	int gridX = 9;
	int gridY = 9;

	int getKilled();

	std::vector<int> level = {
		0, 1, 1, 1, 1, 1, 1, 1, 0,
		1, 1, 1, 2, 1, 2, 1, 1, 1,
		1, 1, 3, 3, 2, 3, 3, 1, 1,
		2, 3, 1, 1, 1, 1, 1, 3, 1,
		2, 2, 2, 1, 1, 1, 1, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2,
		3, 2, 2, 1, 1, 1, 2, 2, 2,
		3, 2, 2, 3, 3, 3, 2, 2, 3,
		0, 3, 3, 3, 3, 3, 3, 3, 0,
	};
};

