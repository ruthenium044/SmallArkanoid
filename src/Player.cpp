#include "Player.h"
#include <iostream>

Player::Player() : sprite({ 0, 0, 0, 0 })
{
}

Player::Player(SDL_Rect src, int scale) : sprite(src)
{
	this->src = src;
	this->scale = scale;

	x = SCREEN_WIDTH / 2 - src.w * scale / 2;
}

Player::~Player()
{
}

void Player::draw(SDL_Rect dst)
{
	SDL_Rect temp = { x, dst.y, dst.w, dst.h };
	sprite.render(temp);
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
