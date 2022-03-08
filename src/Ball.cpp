#include "Ball.h"
#include "Engine.h"
#include "Block.h"
#include <iostream>

Ball::Ball()
{
}

Ball::Ball(SDL_Rect src, float scale, float y)
	: sprite(src), scale(scale), y(y), isActive(true)
{
	x = SCREEN_WIDTH / 2.0f;
	startX = x;
	startY = y;
	velX = startVelX;
	velY = startVelY;
	r = (float) src.w * scale / 4.0f;
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
	SDL_FRect dst{ x - r * 2, y - r * 2, r * scale, r * scale };
	sprite.render(dst);
}

void Ball::collide(float dt, bool isLeft, Line collider)
{
	if (!isActive || isDocked)
	{
		return;
	}

	velY = -velY;
	
	float playerX = collider.a.x;
	float length = collider.b.x;
	float hitPoint = x;
	float proportion = (x - collider.a.x) * 10;
	std::cout << proportion << std::endl;

	if (isLeft)
	{
		velX = -proportion;
	}
	else
	{
		velX = proportion;
	}
	y = startY;
}

void Ball::update(float dt, std::vector<Block>& blocks, int playerX, float offset)
{
	if (engine::checkInput(SDL_SCANCODE_SPACE))
	{
		isDocked = false;
	}

	if (isDocked)
	{
		x = playerX;
	}

	if (!isActive || isDocked)
	{
		return;
	}

	float dx = velX * dt;
	float dy = velY * dt;

	checkLose(dy);
	checkCollisions(dx, blocks, offset, dy);

	x += dx;
	y += dy;
	collider = { x, y, r * scale / 2.0f };
}

void Ball::checkCollisions(float dx, std::vector<Block>& blocks, float offset, float dy)
{
	if (!step(dx, 0.0f, blocks) ||
		x + dx < r + offset || x + dx >= SCREEN_WIDTH - r - offset)
	{
		velX = -velX;
	}
	if (!step(0.0f, dy, blocks) || y + dy < r + offset)
	{
		velY = -velY;
	}
}

void Ball::checkLose(float dy)
{
	if (y + dy >= SCREEN_HEIGHT + 2 * r)
	{
		isActive = false;
		reset();
	}
}

void Ball::reset()
{
	//todo maybe add timer
	x = startX;
	y = startY;
	velX = startVelX;
	velY = -startVelY;
	isActive = true;
	isDocked = true;
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
	return true;
}
