#include "Player.h"
#include "Engine.h"
#include "Level.h"

Player::Player() 
{
}

Player::Player(SDL_Rect src, float scale, float y)
	: sprite(src), src(src), scale(scale), y(y)
{
	x = SCREEN_WIDTH / 2 - src.w * scale / 2;
	Ball temp{ {0, 32, 5, 5}, scale, y - 2.5f * scale};
	balls.push_back(temp);
}

Player::~Player()
{
}

void Player::draw()
{
	SDL_FRect dst = { x, y, src.w * scale, src.h * scale };
	sprite.render(dst);

	for (auto& ball : balls)
	{
		ball.draw();
	}
}

void Player::update(float dt, float offset, Level& level)
{
	tryMove(dt);
	tryShoot(dt);

	x = SDL_clamp(x, offset, SCREEN_WIDTH - src.w * scale - offset);
	mid = x + src.w * scale / 2;
	collider = { x, y, x + src.w * scale, y };

	//how to deal with this
	updateBalls(dt, level, offset);

	collideBalls(dt);
}

void Player::collideBalls(float dt)
{
	for (auto& ball : balls)
	{
		if (collision::intersect(collider, ball.collider))
		{
			ball.collide(dt, { mid, collider.a.y });
		}
	}
}

void Player::updateBalls(float dt, Level& level, float offset)
{
	for (auto& ball : balls)
	{
		ball.update(dt, level.blocks, mid, offset);
	}
}

void Player::tryMove(float dt)
{
	if (engine::checkInput(SDL_SCANCODE_A))
	{
		x -= speed * dt;
	}
	if (engine::checkInput(SDL_SCANCODE_D))
	{
		x += speed * dt;
	}
}

void Player::tryShoot(float dt)
{
	shootTimer -= dt;
	if (engine::checkInput(SDL_SCANCODE_SPACE) && shootTimer < 0.0f)
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

void Player::getAmmo()
{
	Ball temp{ {0, 32, 5, 5}, scale, collider.a.y - 2.5f * scale };
	balls.push_back(temp);
}
