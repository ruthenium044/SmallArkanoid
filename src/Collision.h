#pragma once
#include "Shapes.h"
#include <SDL/SDL.h>

namespace collision
{
	//main reference for the logic:
	//http://www.jeffreythompson.org/collision-detection/table_of_contents.php
	bool intersect(const Circle& circle1, const Circle& circle2);
	bool intersect(const SDL_FRect& square1, const Circle& circle2);
	bool intersect(const Line& line, const Circle& circle);
	bool intersect(const Point& point, const Circle& circle);
	bool intersect(const Line& line, const Point& point);
}