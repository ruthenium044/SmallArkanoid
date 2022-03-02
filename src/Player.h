#pragma once
#include "Sprite.h"
#include "Engine.h"

class Player
{
public:
	Player();
	Player(SDL_Rect src, int scale);
	~Player();

	void draw(SDL_Rect dst);
	void update(float dt, int offset);

private:
	Sprite sprite;
	SDL_Rect src;
	int scale;

	float x;
	int speed = 150;
};
