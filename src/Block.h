#pragma once
#include "Sprite.h"

class Block
{
public:
	Block();
	Block(SDL_Rect src);
	~Block();

	void draw(SDL_Rect dst);

private:
	Sprite sprite;
	bool isActive;
};
