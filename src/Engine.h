#pragma once
#include <SDL/SDL_scancode.h>
#include "Shapes.h"

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 600;

struct SDL_Texture;
struct SDL_Rect;

namespace engine
{
	void init();

	void registerInput(SDL_Scancode key, bool state);
	bool checkInput(SDL_Scancode key); 

	bool collision(const Circle& circle1, const Circle& circle2);
	bool collision(const SDL_Rect& square1, const Circle& circle2);

	void render();
	void drawRect(SDL_Rect rect);
	void drawTexture(SDL_Rect src, SDL_Rect dst);
	void loadTexture(const char* path);

	void present();
	void close();
}
