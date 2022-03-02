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

    bool collision(const Square& square, const Circle& circle)
    {
        float testX = circle.x;
        float testY = circle.y;
        if (circle.x < square.x) 
        {
            testX = square.x;
        }
        else if (circle.x > square.x + square.w)
        {
            testX = square.x + square.w;
        }

        if (circle.y < square.y) 
        {
            testY = square.y;
        }
        else if (circle.y > square.y + square.h)
        {
            testY = square.y + square.h;
        }

        float distX = circle.x - testX;
        float distY = circle.y - testY;
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