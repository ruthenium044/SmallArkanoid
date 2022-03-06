#include "Block.h"

Block::Block()
{
}

Block::Block(SDL_Rect src, int scale, int x, int y)
	: sprite(src), isActive(true)
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
	isActive = false;
}
