#pragma once
#include <SDL/SDL.h>

class CustomTexture
{
public:
    CustomTexture(const char* path);
    ~CustomTexture();

    void render(SDL_Rect src, SDL_Rect dst);

private:
    SDL_Texture* texture;
};