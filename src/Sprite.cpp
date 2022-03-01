#include "Sprite.h"

Sprite::Sprite(CustomTexture* texture, SDL_Rect src)
{
	this->texture = texture;
	this->src = src;
}

Sprite::~Sprite()
{

}

void Sprite::render(SDL_Rect dst)
{
	texture->render(src, dst);
}
