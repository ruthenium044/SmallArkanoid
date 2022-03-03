#include "Level.h"

Level::Level() 
	
{
}

Level::Level(SDL_Rect src, int scale, int offsetX, int offsetY, int gridX, int gridY)
	: gridX(gridX), gridY(gridY)
{
	for (int y = 0; y < gridX; y++)
	{
		for (int x = 0; x < gridY; x++)
		{
			if (level[y * gridX + x] == 1)
			{
				Block temp{ src, scale, x * src.w * scale + offsetX, y * src.h * scale + offsetY };
				blocks.push_back(temp);
			}
			else if(level[y * gridX + x] == 2)
			{
				SDL_Rect tempSrc = { src.x, src.h, src.w, src.h };
				Block temp{ tempSrc, scale, x * src.w * scale + offsetX, y * src.h * scale + offsetY };
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

void Level::draw()
{
	for (int y = 0; y < gridY; y++)
	{
		for (int x = 0; x < gridX; x++)
		{
			blocks[y * gridX + x].draw();
		}
	}
}

