#include "Engine.h"
#include <SDL/SDL_image.h>

namespace engine
{
    static SDL_Window* window;
    static SDL_Renderer* renderer;
    static SDL_Texture* mainTexture;
    static SDL_Texture* backgroundTexture;
    static bool keys[SDL_NUM_SCANCODES] = { false };

    SDL_Color black{ 129, 151, 150, 255 };
    SDL_Color blue{ 164, 221, 216, 255 };
    SDL_Color yellow{ 232, 193, 112, 255 };

    void init()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow("Russky voyenny korabl, idi nahuy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }

    void registerInput(SDL_Scancode key, bool state)
    {
        keys[key] = state;
    }

    bool checkInput(SDL_Scancode key)
    {
        return keys[key];
    }

    void render()
    {
        SDL_RenderClear(renderer);
    }

    void drawBg()
    {
        SDL_Rect src{ 0, 0, 176, 210};
        SDL_FRect dst{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderCopyF(renderer, backgroundTexture, &src, &dst);
    }

    void drawRect(SDL_FRect rect)
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderDrawRectF(renderer, &rect);
    }

    void drawLine(Line line)
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderDrawLineF(renderer, line.a.x, line.a.y, line.b.x, line.b.y);
    }

    void drawCircle(Circle circle)
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        int resolution = 48;
        float step = (2 * 3.14f) / resolution;

        for (int i = 0; i < resolution; ++i)
        {
            float angle = step * i;
            float x1 = cos(angle);
            float y1 = sin(angle);

            float next_angle = step * (i + 1);
            float x2 = cos(next_angle);
            float y2 = sin(next_angle);

            SDL_RenderDrawLine(renderer,
                x1 * circle.r + circle.x,
                y1 * circle.r + circle.y,
                x2 * circle.r + circle.x,
                y2 * circle.r + circle.y
            );
        }
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    }

    void drawTexture(SDL_Rect src, SDL_FRect dst)
    {
        SDL_RenderCopyF(renderer, mainTexture, &src, &dst);
    }

    void loadTextures(const char* path, const char* bgPath)
    {
        mainTexture = IMG_LoadTexture(renderer, path);
        backgroundTexture = IMG_LoadTexture(renderer, bgPath);
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