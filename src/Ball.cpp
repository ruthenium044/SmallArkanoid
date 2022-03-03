#include "Ball.h"
#include "Engine.h"


Ball::Ball()
{
}

Ball::Ball(SDL_Rect src, int scale, float y, int size)
	: sprite(src), scale(scale), size(size), y(y), isActive(true)
{
	x = SCREEN_WIDTH / 2 - src.w * scale / 2;
	r = size * scale / 2;
}

Ball::~Ball()
{
}

void Ball::draw()
{
	if (isActive)
	{
		SDL_Rect dst{ (int) x, (int) y, size * scale, size * scale };
		sprite.render(dst);
	}
}

void Ball::collide()
{
	//turn around
}

void Ball::update(float dt)
{
	//x += speed * dt;
	y -= speed * dt;
}
