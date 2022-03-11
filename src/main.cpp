#include <SDL/SDL.h>
#include "Engine.h"
#include "Collision.h"
#include "Block.h"
#include "Player.h"
#include "Level.h"
#include "Ball.h"
#include <iostream>
#include <vector>

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

	Ball temp{ {0, 32, 5, 5}, scale, screenY - blockSrc.h / 2 * scale + 2 };
	std::vector<Ball> balls;
	balls.push_back(temp);

	bool running = true;
	Uint64 prevTicks = SDL_GetPerformanceCounter();

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

		int killed = level.getKilled();
		if (killed % 10 == 0 && savedKills != killed)
		{
			savedKills = killed;
			Ball temp{ {0, 32, 5, 5}, scale, screenY - blockSrc.h / 2 * scale + 2 };
			balls.push_back(temp);
		}

		//update
		player.update(deltaTime, marginX);

		for (auto& ball: balls)
		{
			ball.update(deltaTime, level.blocks, player.mid, marginX);
		}

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

		for (auto& ball : balls)
		{
			if (collision::intersect(player.collider, ball.collider))
			{
				ball.collide(deltaTime, { player.mid, player.collider.a.y });
				player.collide();
			}
		}
	
		//render
		engine::render();
		engine::drawBg();
		level.draw();
		player.draw();
		for (auto& ball : balls)
		{
			ball.draw();
		}

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
		SDL_Delay(16);
	}
	
	engine::close();

	return 0;
}