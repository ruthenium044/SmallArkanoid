#pragma once
#include "Sprite.h"
#include "Engine.h"
#include "Shapes.h"

class Player
{
public:
	Player();
	Player(SDL_Rect src, float scale, float y);
	~Player();

	void draw();
	void collide();
	void update(float dt, float offset);

	Line collider{ 0, 0, 0, 0 };
	float mid = 0;

private:
	Sprite sprite{ {0, 0, 0, 0} };
	SDL_Rect src{ 0, 0, 0, 0 };
	float scale = 0;

	float x = 0;
	float y = 0;
	int speed = 400;
};
