#pragma once
#include "Sprite.h"
#include "Engine.h"

class Player
{
public:
	Player();
	Player(SDL_Rect src, int scale, float y);
	~Player();

	void draw();
	void update(float dt, int offset);

private:
	Sprite sprite{ {0, 0, 0, 0} };
	SDL_Rect src{0, 0, 0, 0};
	int scale = 0;

	float x = 0;
	float y = 0;
	int speed = 200;
};