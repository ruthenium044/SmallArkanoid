#ifndef INCLUDED_BALL_H
#define INCLUDED_BALL_H

#include "Sprite.h"
#include "Shapes.h"
#include "Block.h"
#include <vector>
#include "Player.h"

class Ball
{
public:
	Ball();
	Ball(SDL_Rect src, float scale, float y);
	~Ball();

	void draw();
	void collide(float dt, Point mid);
	void setNewDirection(Point& mid);
	void update(float dt, std::vector<Block>& blocks, int playerX, float offset);
	void checkCollisions(float dx, std::vector<Block>& blocks, float offset, float dy);
	void checkLose(float dy, int playerX);
	void reset(int playerX);
	bool step(float dx, float dy, std::vector<Block>& blocks);

	Circle collider{ 0, 0, 0 };
	
private:
	float x = 0.0f;
	float y = 0.0f;
	float r = 0.0f;

	float velX = 0;
	float velY = 0;

	int speed = 300;
	float startVelX = 0.0f;
	float startVelY = -speed;

	bool isActive = false;
	bool isDocked = true;
	Sprite sprite{ {0, 0, 0, 0} };

	float startX = 0;
	float startY = 0;
	float scale = 0.0f;
};
#endif // !INCLUDED_BALL_H 