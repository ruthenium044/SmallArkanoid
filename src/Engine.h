#pragma once
#include <SDL/SDL_scancode.h>
#include "Shapes.h"
#include <SDL/SDL.h>

const int SCREEN_WIDTH = 660;
const int SCREEN_HEIGHT = 800;

struct SDL_Texture;
struct SDL_Rect;

namespace engine
{
	 void init();

	void registerInput(SDL_Scancode key, bool state);
	bool checkInput(SDL_Scancode key); 

	//main reference for the logic:
	//http://www.jeffreythompson.org/collision-detection/table_of_contents.php
	bool collision(const Circle& circle1, const Circle& circle2);
	bool collision(const SDL_FRect& square1, const Circle& circle2);
	bool collision(const Line& line, const Circle& circle);
	bool collision(const Point& point, const Circle& circle);
	bool collision(const Line& line, const Point& point);

	void render();
	void drawRect(SDL_FRect rect);
	void drawLine(Line line);
	void drawCircle(Circle circle);
	void drawTexture(SDL_Rect src, SDL_FRect dst);
	void loadTexture(const char* path);

	void present();
	void close();
}
