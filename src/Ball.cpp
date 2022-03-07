#include "Ball.h"
#include "Engine.h"
#include "Block.h"

Ball::Ball()
{
}

Ball::Ball(SDL_Rect src, float scale, float y)
	: sprite(src), scale(scale), y(y), isActive(true)
{
	x = SCREEN_WIDTH / 2.0f - (float) src.w * scale / 2.0f;
	startX = x;
	startY = y;
	velX = startVelX;
	velY = startVelY;
	r = (float) src.w * scale / 2.0f;
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
	SDL_FRect dst{ x, y, r * scale / 2.0f, r * scale / 2.0f };
	sprite.render(dst);
}

void Ball::collide(float dt, bool isLeft)
{
	velY = -velY;
	if (isLeft)
	{
		velX = -startVelX;
	}
	else
	{
		velX = startVelX;
	}
}

void Ball::update(float dt, std::vector<Block>& blocks)
{
	if (!isActive)
	{
		return;
	}

	//try collide
	float dx = velX * dt;
	float dy = velY * dt;

	if (!step(dx, 0.0f, blocks)) //if it collides on x axis flip
	{
		velX = -velX;
	}
	if (!step(0.0f, dy, blocks)) //if it collider on y axis flip
	{
		velY = -velY;
	}
	x += dx;
	y += dy;
	collider = { x, y, r * scale / 2.0f };
}

void Ball::reset()
{
	//SDL_Delay(600);
	x = startX;
	y = startY;
	velX = startVelX;
	velY = -startVelY;
	isActive = true;
}

bool Ball::step(float dx, float dy, std::vector<Block>& blocks)
{
	Circle nextCollider{ collider.x + dx, collider.y + dy, collider.r };
	
	for (auto& block : blocks)
	{
		if (!block.isActive)
		{
			continue;
		}
		if (engine::collision(block.collider, nextCollider))
		{
			block.collide();
			return false;
		}
	}
	if (x + dx < 0.0f || x + dx >= SCREEN_WIDTH || y + dy < 0.0f)
	{
		return false;
	}
	else if (y + dy >= SCREEN_HEIGHT)
	{
		isActive = false;
		reset();
		return false;
	}
	return true;
}
