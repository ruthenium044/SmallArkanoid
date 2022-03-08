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
	SDL_FRect dst = { x, y, src.w * scale, src.h * scale };
	sprite.render(dst);
}

void Player::collide()
{
}

void Player::update(float dt, float offset)
{
	if (engine::checkInput(SDL_SCANCODE_A))
	{
		x -= speed * dt;
	}
	if (engine::checkInput(SDL_SCANCODE_D))
	{
		x += speed * dt;
	}
	x = SDL_clamp(x, offset, SCREEN_WIDTH - src.w * scale - offset);
	
	float w = src.w * scale;
	float h = src.h * scale;
	mid = x + w / 2;

	colliderL = { x, y, mid, y };
	colliderR = { mid, y, x + w, y };
}
