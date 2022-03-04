//#include "Engine.h"
#include <SDL/SDL.h>
#include "Engine.h"
#include "Sprite.h"
#include "Block.h"
#include "Player.h"
#include "Level.h"
#include "Ball.h"

int main()
{
	engine::init();
	engine::loadTexture("tiles.bmp");

	SDL_Rect blockSrc{ 0, 0, 16, 6 };
	int scale = 3;
	int marginX = 10;
	int marginY = 50;
	float screenY = SCREEN_WIDTH - (float)marginX + (float)marginY;

	Level level{ blockSrc, scale, marginX, marginY, 10, 10   };
	Player player{ {0, 12, blockSrc.w, blockSrc.h}, scale, screenY };
	Ball ball{ {0, 18, 4, 4}, scale, screenY - blockSrc.h * scale - 4, 4 };

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
		ball.update(deltaTime);

		//collision
		for (auto& block : level.blocks)
		{
			if (engine::collision(block.collider, ball.collider))
			{
				if (block.isActive)
				{
					block.collide();
					ball.collide(deltaTime);
				}
				
			}
		}

		if (engine::collision(player.collider, ball.collider))
		{
			player.collide();
			ball.collide(deltaTime);
		}
	
		//render
		engine::render();
	
		level.draw();
		player.draw();
		ball.draw();

		engine::drawRect(player.collider);
		engine::drawRect({  (int) ball.collider.x, 
							(int) ball.collider.y,
							(int) ball.collider.r,
							(int) ball.collider.r });
		for (auto& block : level.blocks)
		{
			if (block.isActive)
			{
				engine::drawRect(block.collider);
			}
		}
		engine::present();

		SDL_Delay(16);
	}
	
	engine::close();

	return 0;
}