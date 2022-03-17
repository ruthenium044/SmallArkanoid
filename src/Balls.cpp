#include "Balls.h"
#include "Engine.h"
#include "Collision.h"

Balls::Balls()
{
	

}

Balls::Balls(SDL_Rect src, float scale, float y)
	: src(src), scale(scale), spawnY(y)
{
	Ball temp{ src, scale, y - 2.5f * scale };
	balls.push_back(temp);
}

Balls::~Balls()
{
}

void Balls::tryShoot(float dt)
{
	shootTimer -= dt;
	if (engine::getKeyPressed(SDL_SCANCODE_SPACE) && shootTimer < 0.0f)
	{
		for (auto& ball : balls)
		{
			if (ball.isDocked)
			{
				ball.undock();
				shootTimer = shootRate;
				break;
			}
		}
	}
}

void Balls::addBall()
{
	Ball temp{ src, scale, spawnY - 2.5f * scale };
	balls.push_back(temp);
}

void Balls::update(float dt, Level& level, Player player, float margin)
{
	tryShoot(dt);
	int i = 0;
	for (auto& ball : balls)
	{
		ball.update(dt, level.blocks, player.mid, margin);
		checkLose(ball, i, player.mid);
		collide(player, ball, dt);
		i++;
	}
}

void Balls::checkLose(Ball& ball, int i, int x)
{
	if (!ball.isDocked && ball.collider.y >= SCREEN_HEIGHT)
	{
		if (balls.size() > 1)
		{
			balls.erase(balls.begin() + i);
		}
		else
		{
			deathCounter++;
			ball.reset(x);
		}
	}
}

void Balls::collide(Player& player, Ball& ball, float dt)
{
	if (collision::intersect(player.collider, ball.collider))
	{
		ball.collide(dt, { player.mid, player.collider.a.y });
	}
}

void Balls::draw()
{
	for (auto& ball : balls)
	{
		ball.draw();
	}
}
