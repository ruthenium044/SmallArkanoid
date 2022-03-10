#include "Ball.h"
#include "Engine.h"
#include "Collision.h"
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

	//Point mid = { player.mid, player.collider.a.y};
	//Point ball{ x - mid.x, y - mid.y };
	//float len = sqrt(ball.x * ball.x + ball.y * ball.y);
	//Point dir{ ball.x / len,  ball.y / len };
	//Line normalizedDir{(dir.x * 100.0f) + mid.x, (dir.y * 100.0f) + mid.y, mid.x, mid.y };
	//engine::drawLine(normalizedDir);
}

void Ball::collide(float dt, Point mid)
{
	if (!isActive || isDocked)
	{
		return;
	}

	setNewDirection(mid);
	y = startY;
}

void Ball::setNewDirection(Point& mid)
{
	Point ball{ x - mid.x, y - mid.y + 50 };
	float len = sqrt(ball.x * ball.x + ball.y * ball.y);
	Point dir{ ball.x / len,  ball.y / len };

	velX = speed * dir.x;
	velY = speed * -dir.y;
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
		velX = -velX;
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
		if (collision::intersect(block.collider, nextCollider))
		{
			block.collide();
			return false;
		}
	}
	x += dx;
	y += dy;
	return true;
}
