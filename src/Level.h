#pragma once
#include <vector>
#include "Block.h"
#include "Coords.h"

class Level
{
public:
	Level();
	Level(SDL_Rect src, float scale, float offsetX, float offsetY);
	~Level();

	void draw();

	int gridX = 10;
	int gridY = 10;
	std::vector<Block> blocks;

private:

	std::vector<int> level = {
		0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		2, 1, 1, 1, 1, 1, 1, 1, 1, 2,
		2, 1, 1, 1, 1, 1, 1, 1, 1, 2,
		2, 2, 2, 1, 1, 1, 1, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		3, 2, 2, 2, 2, 2, 2, 2, 2, 3,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		0, 3, 3, 3, 3, 3, 3, 3, 3, 0,
		0, 0, 3, 3, 3, 3, 3, 3, 0, 0,
	};
};

