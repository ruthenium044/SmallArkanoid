#include "Sprite.h"
#include "Engine.h"

Sprite::Sprite(SDL_Rect src) : src(src)
{
}

Sprite::~Sprite()
{

}

void Sprite::render(SDL_Rect dst)
{
	engine::drawTexture(src, dst);
}
