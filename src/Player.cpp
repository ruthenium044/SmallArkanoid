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
}

Player::~Player()
{
}

void Player::draw()
{
	SDL_FRect dst = { x, y, src.w * scale, src.h * scale };
	sprite.render(dst);
}

void Player::update(float dt, float offset, Level& level)
{
	if (engine::getKeyDown(SDL_SCANCODE_A))
	{
		x -= speed * dt;
	}
	if (engine::getKeyDown(SDL_SCANCODE_D))
	{
		x += speed * dt;
	}

	x = SDL_clamp(x, offset, SCREEN_WIDTH - src.w * scale - offset);
	mid = x + src.w * scale / 2;
	collider = { x, y, x + src.w * scale, y };
}