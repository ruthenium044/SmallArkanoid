#include <SDL/SDL.h>
#include "Engine.h"
#include "Player.h"
#include "Level.h"
#include "Ball.h"
#include <iostream>
#include "Balls.h"

int main()
{
	engine::init();
	engine::loadTextures("Warship.png", "BG.png");

	SDL_Rect blockSrc{ 0, 0, 16, 9 };
	float scale = 4;
	float margin = 48;
	float screenY = SCREEN_HEIGHT - margin;

	engine::loadFont("AsepriteFont.ttf", 16 * scale);
	engine::setText("Press space");

	Level level{ blockSrc, scale, margin + 4 * scale, margin + 4 * scale };
	Player player{ {32, 9, blockSrc.w, blockSrc.h / 2}, scale, screenY };
	Balls balls{ {32, 13, 5, 5}, scale, screenY };

	Uint64 prevTicks = SDL_GetPerformanceCounter();
	bool running = true;
	int savedKills = 0;

	enum class State
	{
		START,
		GAME,
		LOSE,
		WIN
	};
	State cuttentState = State::START;

	while (running)
	{
		engine::increaseFrame();
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
				if (event.key.repeat)
				{
					break;
				}
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
		engine::render();
		engine::drawBg();

		if (cuttentState == State::GAME)
		{
			if (balls.deathCounter >= balls.health)
			{
				engine::setText("You lose bye");
				cuttentState = State::LOSE;
			}
			player.update(deltaTime, margin, level);
			balls.update(deltaTime, level, player, margin);
			level.update(running, savedKills, player);
		
			int killed = level.getKilled();
			if (killed == level.blocks.size())
			{
				engine::setText("You win bye");
				cuttentState = State::WIN;
			}
			else if (killed % 10 == 0 && savedKills != killed)
			{
				savedKills = killed;
				balls.addBall();
			}
			player.draw();
			balls.draw();
			level.draw();
		}
		else
		{
			if (engine::getKeyPressed(SDL_SCANCODE_SPACE))
			{
				if (cuttentState == State::START)
				{
					cuttentState = State::GAME;
				}
				else
				{
					running = false;
				}
			}
			engine::drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		}
		engine::present();
		SDL_Delay(16);
	}
	engine::close();
	return 0;
}