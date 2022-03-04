#include "Engine.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

namespace engine
{
    static SDL_Window* window;
    static SDL_Renderer* renderer;
    static SDL_Texture* mainTexture;

    static bool keys[SDL_NUM_SCANCODES] = { false };

    void init()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow("Russky voyenny korabl, idi nahuy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }

    void registerInput(SDL_Scancode key, bool state)
    {
        keys[key] = state;
    }

    bool checkInput(SDL_Scancode key)
    {
        return keys[key];
    }

    bool collision(const Circle& circle1, const Circle& circle2)
    {
        float distX = circle1.x - circle2.x;
        float distY = circle1.y - circle2.y;
        float distance = sqrt((distX * distX) + (distY * distY));
        if (distance <= circle1.r + circle2.r) 
        {
            return true;
        }
        return false;
    }

    bool collision(const SDL_Rect& square, const Circle& circle)
    {
        float x = circle.x;
        float y = circle.y;
        if (circle.x < square.x) 
        {
            x = square.x;
        }
        else if (circle.x > square.x + square.w)
        {
            x = square.x + square.w;
        }

        if (circle.y < square.y) 
        {
            y = square.y;
        }
        else if (circle.y > square.y + square.h)
        {
            y = square.y + square.h;
        }

        float distX = circle.x - x;
        float distY = circle.y - y;
        float distance = sqrt((distX * distX) + (distY * distY));

        if (distance <= circle.r) 
        {
            return true;
        }
        return false;
    }

    void render()
    {
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    }

    void drawRect(SDL_Rect rect)
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    }

    void drawTexture(SDL_Rect src, SDL_Rect dst)
    {
        SDL_RenderCopy(renderer, mainTexture, &src, &dst);
    }

    void loadTexture(const char* path)
    {
        mainTexture = IMG_LoadTexture(renderer, path);
    }

    void present()
    {
        SDL_RenderPresent(renderer);
    }

    void close()
    {
        SDL_DestroyWindow(window);
        window = nullptr;
        SDL_Quit();
    }
}