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
	if (!isActive)
	{
		return;
	}
	SDL_Rect dst{ (int)x, (int)y, size * scale, size * scale };
	sprite.render(dst);
}

void Ball::collide(float dt)
{
	//turn around
	// vector x y

	
	velY = -velY;// *0.8;
	//collide 
	
}

void Ball::update(float dt)
{
	if (!isActive)
	{
		return;
	}

	//try collide

	//if (!step(velX * dt, 0)) //iff it collides on x axis flip
	//{
	//	velX = -velX;// * 0.8;
	//}
	//if (!step(0, velY * dt)) //if it collider on y axis flip
	//{

	//move
	x += velX * dt;
	y += velY * dt;
	collider = { x, y, r * scale };
}

bool Ball::step(float dx, float dy)
{
	//create the next position

	//run the collision check
	//if interesct just return false

	//check if its bounds or not and shit

	//if nothing was hit, move and return
	// 
	//Circle circle = { x + dx, y + dy, 4 };
	//draw_circle(circle);

	//for (int i = 0; i < BRICK_MAX; ++i)
	//{
	//	Brick& brick = bricks[i];
	//	if (!brick.alive)
	//		continue;

	//	AABB box = AABB::make_from_position_size(brick.x, brick.y, brick.w, brick.h);

	//	if (aabb_circle_intersect(box, circle))
	//		return false;
	//}

	//// Check collisions with game borders
	if (x + dx < 0 || x + dx >= SCREEN_WIDTH || y + dy < 0 || y + dy >= SCREEN_HEIGHT)
	{
		return false;
	}

	x += dx;
	y += dy;
	return true;
}
