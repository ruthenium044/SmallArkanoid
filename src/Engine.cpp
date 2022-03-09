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

    bool collision(const SDL_FRect& square, const Circle& circle)
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

    bool collision(const Line& line, const Circle& circle)
    {
        if (collision(line.a, circle) || collision(line.b, circle))
        {
            return true;
        }

        float distX = line.a.x - line.b.x;
        float distY = line.a.y - line.b.y;
        float length = sqrt((distX * distX) + (distY * distY));

        float dot = (((circle.x - line.a.x) * (line.b.x - line.a.x)) +
            ((circle.y - line.a.y) * (line.b.y - line.a.y))) / pow(length, 2);

        float closestX = line.a.x + (dot * (line.b.x - line.a.x));
        float closestY = line.a.y + (dot * (line.b.y - line.a.y));

        Point point{ closestX, closestY };
        bool onSegment = collision(line, point);
        if (!onSegment)
        {
            return false;
        }

        distX = closestX - circle.x;
        distY = closestY - circle.y;

        float distance = sqrt((distX * distX) + (distY * distY));

        if (distance <= circle.r)
        {
            return true;
        }
        return false;
    }

    bool collision(const Point& point, const Circle& circle)
    {
        float distX = point.x - circle.x;
        float distY = point.y - circle.y;
        float distance = sqrt((distX * distX) + (distY * distY));
        if (distance <= circle.r) {
            return true;
        }
        return false;
    }

    bool collision(const Line& line, const Point& point)
    {
        float dist1 = sqrt(pow(point.x - line.a.x, 2) + pow(point.y - line.a.y, 2));
        float dist2 = sqrt(pow(point.x - line.b.x, 2) + pow(point.y - line.b.y, 2));
        float lineLength = sqrt(pow(line.a.x - line.b.x, 2) + pow(line.a.y - line.b.y, 2));

        if (dist1 + dist2 >= lineLength && dist1 + dist2 <= lineLength)
        {
            return true;
        }
        return false;
    }

    SDL_Color black{ 129, 151, 150, 255 };
    SDL_Color blue{ 164, 221, 216, 255 };
    SDL_Color yellow{ 232, 193, 112, 255 };

    void render()
    {
        SDL_RenderClear(renderer);
        drawBg();
    }

    void drawBg()
    {
        SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
        SDL_FRect rect{ 0,0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderFillRectF(renderer, &rect);

        //SDL_SetRenderDrawColor(renderer, blue.r, blue.g, blue.b, blue.a);
        //SDL_FRect rect1{ 0,0, SCREEN_WIDTH, SCREEN_HEIGHT / 4 };
        //SDL_RenderFillRectF(renderer, &rect1);
        //
        //SDL_SetRenderDrawColor(renderer, yellow.r, yellow.g, yellow.b, yellow.a);
        //SDL_FRect rect2{ 0, SCREEN_HEIGHT / 4, SCREEN_WIDTH, SCREEN_HEIGHT / 4 };
        //SDL_RenderFillRectF(renderer, &rect2);
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