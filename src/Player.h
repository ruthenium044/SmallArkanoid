#ifndef INCLUDED_PLAYER_H
#define INCLUDED_PLAYER_H
#include <vector>
#include "Sprite.h"
#include "Shapes.h"
#include "Collision.h"
#include "Ball.h"

class Level;

class Player
{
public:
	Player();
	Player(SDL_Rect src, float scale, float y);
	~Player();

	void draw();
	void update(float dt, float offset, Level& level);

	Line collider{ 0, 0, 0, 0 };
	float mid = 0;

private:
	Sprite sprite{ {0, 0, 0, 0} };
	SDL_Rect src{ 0, 0, 0, 0 };
	float scale = 0;

	float x = 0;
	float y = 0;
	int speed = 400;
};
#endif // !INCLUDED_PLAYER_H 
