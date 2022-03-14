#include "Block.h"

Block::Block()
{
}

Block::Block(SDL_Rect src, float scale, float x, float y, int hp)
	: sprite(src), hp(hp), isActive(true), startHp(hp)
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
	hp--;
	if (hp < 1)
	{
		isActive = false;
	}
	int temp = startHp - hp;
	SDL_Rect newSrc{ sprite.src.w * temp, sprite.src.y, sprite.src.w, sprite.src.h };
	sprite.updateSrc(newSrc);
}
