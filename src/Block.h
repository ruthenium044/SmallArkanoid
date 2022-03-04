#pragma once
#include "Sprite.h"

class Block
{
public:
	Block();
	Block(SDL_Rect src, int scale, int x, int y);
	~Block();

	void draw();
	void collide();

	SDL_Rect collider{ 0, 0, 0, 0 };
	bool isActive = false;

private:
	int x = 0;
	int y = 0;
	int scale = 0;

	Sprite sprite{ {0, 0, 0, 0} };
};
