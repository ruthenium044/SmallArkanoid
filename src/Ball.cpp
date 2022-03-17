#include "Ball.h"
#include "Engine.h"
#include "Collision.h"

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
	//engine::drawCircle(collider);
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
	if (isDocked)
	{
		x = playerX;
		y = startY;
	}
	if (!isActive || isDocked)
	{
		return;
	}
	float dx = velX * dt;
	float dy = velY * dt;

	checkCollisions(dx, blocks, offset, dy);
	collider = { x, y, r * scale / 2.0f };
}

void Ball::undock()
{
	isDocked = false;
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


void Ball::reset(int playerX)
{
	x = playerX;
	y = startY;

	velX = startVelX;
	velY = -startVelY;

	isDocked = true;
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
