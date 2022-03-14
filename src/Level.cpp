#include "Level.h"
#include "Player.h"

Level::Level() 
{
}

Level::Level(SDL_Rect src, float scale, float offsetX, float offsetY)
{
	for (int y = 0; y < gridX; y++)
	{
		for (int x = 0; x < gridY; x++)
		{
			int index = y * gridX + x;
			if (level[index] == 1)
			{
				Block temp{ src, scale, (float) x * src.w * scale + offsetX, (float) y * src.h * scale + offsetY, 3 };
				blocks.push_back(temp);
			}
			else if(level[index] == 2)
			{
				SDL_Rect tempSrc = { src.x, src.h, src.w, src.h };
				Block temp{ tempSrc, scale, (float) x * src.w * scale + offsetX, (float) y * src.h * scale + offsetY, 2 };
				blocks.push_back(temp);
			}
			else if (level[index] == 3)
			{
				SDL_Rect tempSrc = { src.x, src.h * 2, src.w, src.h };
				Block temp{ tempSrc, scale, (float) x * src.w * scale + offsetX, (float) y * src.h * scale + offsetY, 1 };
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

void Level::update(bool& running, int& savedKills, Player& player)
{
	int killed = getKilled();
	if (killed == blocks.size())
	{
		running = false;
	}
	else if (killed % 10 == 0 && savedKills != killed)
	{
		savedKills = killed;

		//how to get rid of this
		player.getAmmo();
	}
}

int Level::getKilled()
{
	killCount = 0;
	for (auto& block : blocks)
	{
		killCount += (int) !block.isActive;
	}
	return killCount;
}

