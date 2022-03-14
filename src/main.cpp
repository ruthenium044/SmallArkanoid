#include <SDL/SDL.h>
#include "Engine.h"
#include "Player.h"
#include "Level.h"
#include "Ball.h"
#include "main.h"

int main()
{
	engine::init();
	engine::loadTextures("Warship.png", "BG.png");

	SDL_Rect blockSrc{ 0, 0, 16, 9 };
	float scale = 4;
	float marginX = 48;
	float marginY = 48;
	float screenY = SCREEN_HEIGHT - marginY;

	Level level{ blockSrc, scale, marginX + 4 * scale, marginY + 4 * scale };
	Player player{ {0, 28, blockSrc.w, blockSrc.h / 2}, scale, screenY };

	Uint64 prevTicks = SDL_GetPerformanceCounter();
	bool running = true;
	int savedKills = 0;

	while (running)
	{
		Uint64 ticks = SDL_GetPerformanceCounter();
		Uint64 dTicks = ticks - prevTicks;
		prevTicks = ticks;
		float deltaTime = (float) dTicks / SDL_GetPerformanceFrequency();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;

			case SDL_KEYDOWN:
			{
				int scancode = event.key.keysym.scancode;
				if (scancode == SDL_SCANCODE_ESCAPE)
				{
					running = false;
				}
				engine::registerInput((SDL_Scancode) scancode, true);
				break;
			}
			case SDL_KEYUP:
			{
				int scancode = event.key.keysym.scancode;
				engine::registerInput((SDL_Scancode) scancode, false);
				break;
			}
			}
		}

		//update
		player.update(deltaTime, marginX, level);
		level.update(running, savedKills, player);
	
		//render
		engine::render();
		engine::drawBg();
		level.draw();
		player.draw();

		//colliders
		//engine::drawLine(player.collider);
		//for (auto& block : level.blocks)
		//{
		//	if (block.isActive)
		//	{
		//		engine::drawRect(block.collider);
		//	}
		//}

		engine::present();
		SDL_Delay(16);
	}
	engine::close();

	return 0;
}

