#pragma once
#include <vector>
#include "Block.h"
#include "Coords.h"

class Level
{
public:
	Level();
	Level(int gridX, int gridY, int blockX, int blockY);
	~Level();

	void draw(int scale, int offsetX, int offsetY);

private:
	int gridX;
	int gridY;

	int blockX;
	int blockY;

	std::vector<Block> blocks;

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

