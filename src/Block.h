#pragma once
#include "Sprite.h"
#include "Shapes.h"

class Block
{
public:
	Block();
	Block(SDL_Rect src, float scale, float x, float y, int hp);
	~Block();

	void draw();
	void collide();

	SDL_FRect collider{ 0, 0, 0, 0 };
	bool isActive = false;

private:
	float x = 0;
	float y = 0;
	float scale = 0;

	int hp = 0;
	int startHp = 0;

	Sprite sprite{ {0, 0, 0, 0} };
};
