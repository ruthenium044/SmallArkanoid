#include "Player.h"
#include <iostream>

Player::Player() 
{
}

Player::Player(SDL_Rect src, float scale, float y)
	: sprite(src), src(src), scale(scale), y(y)
{
	x = SCREEN_WIDTH / 2 - src.w * scale / 2;
}

Player::~Player()
{
}

void Player::draw()
{
	float tempX = x - src.w * scale / 2;
	float tempY = y + src.h * scale / 2;
	SDL_FRect dst = { tempX, tempY, src.w * scale, src.h * scale };
	sprite.render(dst);
}

void Player::collide()
{
}

void Player::update(float dt, float offset)
{
	float w = src.w * scale;
	float h = src.h * scale;
	

	if (engine::checkInput(SDL_SCANCODE_A))
	{
		x -= speed * dt;
		x = SDL_clamp(x, offset, SCREEN_WIDTH - src.w * scale - offset);
	}
	if (engine::checkInput(SDL_SCANCODE_D))
	{
		x += speed * dt;
		x = SDL_clamp(x, offset, SCREEN_WIDTH - src.w * scale - offset);
	}

	colliderL = { x - w / 2, y + h / 2, w / 2, h };
	colliderR = { w / 2 + x - w / 2, y + h / 2, w / 2, h };
}
