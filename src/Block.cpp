#include "Block.h"

Block::Block()
{
}

Block::Block(SDL_Rect src, float scale, float x, float y, int hp)
	: sprite(src), hp(hp), isActive(true)
{
	collider = { x, y, src.w * scale, src.h * scale };
}

Block::~Block()
{
}

void Block::draw()
{
	if (!isActive)
	{
		return;
	}
	sprite.render(collider);
}

void Block::collide()
{
	if (hp <= 0)
	{
		isActive = false;
	}
	hp--;
}
