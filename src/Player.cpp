#include "Player.h"
#include <iostream>

Player::Player() 
{
}

Player::Player(SDL_Rect src, int scale, float y)
	: sprite(src), src(src), scale(scale), y(y)
{
	x = SCREEN_WIDTH / 2 - src.w * scale / 2;
}

Player::~Player()
{
}

void Player::draw()
{
	SDL_Rect dst = { x, y, src.w * scale, src.h * scale };
	sprite.render(dst);
}

void Player::update(float dt, int offset)
{
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
}
