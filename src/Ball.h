#ifndef INCLUDED_BALL_H
#define INCLUDED_BALL_H

#include "Sprite.h"
#include "Shapes.h"
#include "Block.h"
#include <vector>

class Ball
{
public:
	Ball();
	Ball(SDL_Rect src, float scale, float y);
	~Ball();

	void draw();
	void collide(float dt, bool isLeft, Line collider);
	void update(float dt, std::vector<Block>& blocks, int playerX, float offset);
	void checkCollisions(float dx, std::vector<Block>& blocks, float offset, float dy);
	void checkLose(float dy);
	void reset();

	bool step(float dx, float dy, std::vector<Block>& blocks);

	Circle collider{ 0, 0, 0 };
	
private:
	float x = 0.0f;
	float y = 0.0f;
	float r = 0.0f;

	float velX = 0;
	float velY = 0;

	float startVelX = 0.0f;
	float startVelY = -400.0f;

	bool isActive = false;
	bool isDocked = true;
	Sprite sprite{ {0, 0, 0, 0} };

	float startX = 0;
	float startY = 0;
	float scale = 0.0f;
	int speed = 100;
};
#endif // !INCLUDED_BALL_H 