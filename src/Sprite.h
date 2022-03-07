#pragma once
#include <SDL/SDL.h>

class Sprite
{
public:
	Sprite(SDL_Rect src);
	~Sprite();
	void render(SDL_FRect dst);

private:
	SDL_Rect src;
};

