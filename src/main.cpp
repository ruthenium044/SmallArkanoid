//#include "Engine.h"
#include <SDL/SDL.h>
#include "Engine.h"
#include "Sprite.h"
#include "Block.h"
#include "Player.h"
#include "Level.h"
#include "Ball.h"
#include <iostream>

int main()
{
	engine::init();
	engine::loadTexture("Warship.png");

	SDL_Rect blockSrc{ 0, 0, 16, 8 };
	float scale = 4;
	float marginX = 10;
	float marginY = 50;
	float screenY = SCREEN_WIDTH - marginX + marginY;

	Level level{ blockSrc, scale, marginX, marginY };
	Player player{ {0, 24, blockSrc.w, blockSrc.h / 2}, scale, screenY };
	Ball ball{ {0, 32, 5, 5}, scale, screenY - blockSrc.h / 2 * scale + 2 };

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
		ball.update(deltaTime, level.blocks, player.mid, marginX);

		//collision
		/*for (auto& block : level.blocks)
		{
			if (engine::collision(block.collider, ball.collider))
			{
				if (block.isActive)
				{
					block.collide();
					ball.collide(deltaTime);
				}
				
			}
		}*/

		if (engine::collision(player.collider, ball.collider))
		{
			ball.collide(deltaTime, { player.mid, player.collider.a.y });
			player.collide();
		}
	
		//render
		engine::render();
	
		level.draw();
		player.draw();
		ball.draw();

		//colliders
		//engine::drawLine(player.collider);
		//engine::drawCircle(ball.collider);
		//for (auto& block : level.blocks)
		//{
		//	if (block.isActive)
		//	{
		//		engine::drawRect(block.collider);
		//	}
		//}
		engine::present();
	}
	
	engine::close();

	return 0;
}