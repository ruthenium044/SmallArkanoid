//#include "Engine.h"
#include <SDL/SDL.h>
#include "CustomTexture.h"
#include "Engine.h"
#include "Sprite.h"

int main()
{
	engine::init();

	//SDL_Rect SpriteClips[4];
	CustomTexture spriteSheetTexture{ "tiles.bmp" };
	SDL_Rect src{ 0, 0, 16, 16 };
	Sprite sprite{ &spriteSheetTexture, src };

	float x = 100;
	bool pressingA = false;
	bool pressingD = false;

	bool running = true;
	Uint64 prevTicks = SDL_GetPerformanceCounter();

	while (running)
	{
		Uint64 ticks = SDL_GetPerformanceCounter();
		Uint64 dTicks = ticks - prevTicks;
		prevTicks = ticks;
		float dt = (float) dTicks / SDL_GetPerformanceFrequency();

		SDL_Event event;
		if (SDL_PollEvent(&event))
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

				if (scancode == SDL_SCANCODE_A)
				{
					pressingA = true;
				}
				if (scancode == SDL_SCANCODE_D)
				{
					pressingD = true;
				}

				break;
			}
				case SDL_KEYUP:
				{
					int scancode = event.key.keysym.scancode;
					if (scancode == SDL_SCANCODE_A)
					{
						pressingA = false;
					}
					if (scancode == SDL_SCANCODE_D)
					{
						pressingD = false;
					}
					break;
				}
			}
		}

		//player movement
		if (pressingD)
		{
			x += 128 * dt;
		}
		if (pressingA)
		{
			x -= 128 * dt;
		}
		
		engine::render();
		
		SDL_Rect dst{ 100, 100, 32, 32 };
		sprite.render(dst);

		engine::present();

		SDL_Delay(16);
	}
	
	engine::close();

	return 0;
}