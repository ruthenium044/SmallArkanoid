#include "Level.h"

Level::Level() 
	: gridX(0), gridY(0), blockX(0), blockY(0)
{
}

Level::Level(int gridX, int gridY, int blockX, int blockY) 
	: gridX(gridX), gridY(gridY), blockX(blockX), blockY(blockY)
{
	for (int y = 0; y < gridX; y++)
	{
		for (int x = 0; x < gridY; x++)
		{
			if (level[y * gridX + x] == 1)
			{
				Block temp{ {0, 0, blockX, blockY} };
				blocks.push_back(temp);
			}
			else if(level[y * gridX + x] == 2)
			{
				Block temp{ {0, blockY, blockX, blockY} };
				blocks.push_back(temp);
			}
			else
			{
				Block temp{};
				blocks.push_back(temp);
			}
		}
	}
}

Level::~Level()
{
}

void Level::draw(int scale, int offsetX, int offsetY)
{
	for (int y = 0; y < gridY; y++)
	{
		for (int x = 0; x < gridX; x++)
		{
			blocks[y * gridX + x].draw({ 
				x * blockX * scale + offsetX, y * blockY * scale + offsetY, 
				blockX * scale, blockY * scale });
		}
	}
}
