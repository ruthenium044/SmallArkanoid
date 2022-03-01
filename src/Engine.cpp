#include "Engine.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

namespace engine
{
    static SDL_Window* Window;
    static SDL_Renderer* Renderer;

    void init()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        Window = SDL_CreateWindow("Russky voyenny korabl, idi nahuy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }

    void render()
    {
        SDL_RenderClear(Renderer);
        SDL_SetRenderDrawColor(Renderer, 40, 50, 40, 255);
    }

    void drawTexture(SDL_Texture* texture, SDL_Rect src, SDL_Rect dst)
    {
        SDL_RenderClear(Renderer);
        SDL_RenderCopy(Renderer, texture, &src, &dst);
    }

    SDL_Texture* loadTexture(const char* path)
    {
        return IMG_LoadTexture(Renderer, path);
    }

    void present()
    {
        SDL_RenderPresent(Renderer);
    }

    void close()
    {
        SDL_DestroyWindow(Window);
        Window = nullptr;
        SDL_Quit();
    }
}