//#include "Engine.h"
#include <SDL/SDL.h>
#include "Engine.h"
#include "Sprite.h"
#include "Block.h"
#include "Player.h"
#include "Level.h"

int main()
{
	engine::init();
	engine::loadTexture("tiles.bmp");

	SDL_Rect blockSrc{ 0, 0, 16, 6 };
	int scale = 3;
	int marginX = 10;
	int marginY = 50;

	Level level{ 10, 10, blockSrc.w, blockSrc.h};
	Player player{ {0, 12, blockSrc.w, blockSrc.h}, scale };

	bool running = true;
	Uint64 prevTicks = SDL_GetPerformanceCounter();

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
		player.update(deltaTime, marginX);

		//render
		engine::render();
	
		level.draw(scale, marginX, marginX + marginY);

		player.draw({ 0, SCREEN_WIDTH - marginX + marginY, blockSrc.w * scale, blockSrc.h * scale});

		engine::present();

		SDL_Delay(16);
	}
	
	engine::close();

	return 0;
}