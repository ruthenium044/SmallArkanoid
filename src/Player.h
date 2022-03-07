#pragma once
#include "Sprite.h"
#include "Engine.h"

class Player
{
public:
	Player();
	Player(SDL_Rect src, float scale, float y);
	~Player();

	void draw();
	void collide();
	void update(float dt, float offset);

	SDL_FRect colliderL{ 0, 0, 0, 0 };
	SDL_FRect colliderR{ 0, 0, 0, 0 };

private:
	Sprite sprite{ {0, 0, 0, 0} };
	SDL_Rect src{0, 0, 0, 0};
	float scale = 0;

	float x = 0;
	float y = 0;
	int speed = 200;
};
