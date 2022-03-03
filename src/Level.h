#pragma once
#include <vector>
#include "Block.h"
#include "Coords.h"

class Level
{
public:
	Level();
	Level(SDL_Rect src, int scale, int offsetX, int offsetY, int gridX, int gridY);
	~Level();

	void draw();

	int gridX = 0;
	int gridY = 0;
	std::vector<Block> blocks;

private:

	std::vector<int> level = {
		0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		0, 2, 2, 2, 2, 2, 2, 2, 2, 0,
	};
};

