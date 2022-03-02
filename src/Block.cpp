#include "Block.h"

Block::Block() : sprite( {0, 0, 0, 0} )
{
	isActive = false;
}

Block::Block(SDL_Rect src) : sprite(src)
{
	isActive = true;
}

Block::~Block()
{
}

void Block::draw(SDL_Rect dst)
{
	sprite.render(dst);
}
