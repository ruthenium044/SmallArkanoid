#pragma once
#include <SDL/SDL_scancode.h>
#include "Shapes.h"
#include <SDL/SDL.h>

const int SCREEN_WIDTH = 69 * 10;
const int SCREEN_HEIGHT = 420 * 2;

struct SDL_Texture;
struct SDL_Rect;

namespace engine
{
	void init();
	void registerInput(SDL_Scancode key, bool state);
	bool checkInput(SDL_Scancode key); 

	void render();
	void drawBg();
	void drawRect(SDL_FRect rect);
	void drawLine(Line line);
	void drawCircle(Circle circle);
	void drawTexture(SDL_Rect src, SDL_FRect dst);
	void loadTexture(const char* path);

	void present();
	void close();
}
