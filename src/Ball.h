#pragma once
#include "Sprite.h"
#include "Shapes.h"

class Ball
{
public:
	Ball();
	Ball(SDL_Rect src, int scale, float y, int size);
	~Ball();

	void draw();
	void collide(float dt);
	void update(float dt);

	bool step(float dx, float dy);

	Circle collider{ 0, 0, 0 };
	
private:
	float x = 0;
	float y = 0;
	float r = 0;

	float velX = 0;
	float velY = -100;

	bool isActive = false;
	Sprite sprite{ {0, 0, 0, 0} };

	int size = 0;
	int scale = 0;
	int speed = 100;

	int dir = -1;
};
