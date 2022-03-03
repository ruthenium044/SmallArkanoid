#pragma once
#include "Sprite.h"

class Ball
{
public:
	Ball();
	Ball(SDL_Rect src, int scale, float y, int size);
	~Ball();

	void draw();
	void collide();
	void update(float dt);

	float x = 0;
	float y = 0;
	float r = 0;
private:
	Sprite sprite{ {0, 0, 0, 0} };
	bool isActive = false;

	int size = 0;
	int scale = 0;
	int speed = 50;
};
