#pragma once
#include <SDL/SDL.h>
#include "CustomTexture.h"

class Sprite
{
public:
	Sprite(CustomTexture* texture, SDL_Rect src);
	~Sprite();
	void render(SDL_Rect dst);

private:
	CustomTexture* texture;
	SDL_Rect src;
};

