#include "CustomTexture.h"
#include "Engine.h"
#include <SDL/SDL_image.h>

CustomTexture::CustomTexture(const char* path)
{
    texture = engine::loadTexture(path);
}

CustomTexture::~CustomTexture()
{
}

void CustomTexture::render(SDL_Rect src, SDL_Rect dst)
{
    engine::drawTexture(texture, src, dst);
}

