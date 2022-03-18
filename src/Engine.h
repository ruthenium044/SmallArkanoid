#pragma once
#include <SDL/SDL_scancode.h>
#include "Shapes.h"
#include <SDL/SDL.h>

const int SCREEN_WIDTH = 69 * 10 + 14;
const int SCREEN_HEIGHT = 420 * 2;

struct SDL_Texture;
struct SDL_Rect;

struct KeyState
{
	bool state = false;
	int changeFrame = 0;
};

namespace engine
{
	void init();

	void increaseFrame();
	void registerInput(SDL_Scancode key, bool state);
	bool getKeyDown(SDL_Scancode key);
	bool getKeyPressed(SDL_Scancode key);
	bool getKeyReleased(SDL_Scancode key);

	void render();
	void drawBg();
	void drawRect(SDL_FRect rect);
	void drawLine(Line line);
	void drawCircle(Circle circle);

	void drawTexture(SDL_Rect src, SDL_FRect dst);
	void drawText(float x, float y);
	void setText(const char* text);
	void loadTextures(const char* path, const char* bgPath);
	void loadFont(const char* path, int size);

	void present();
	void close();
}
