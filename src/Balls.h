#pragma once
#include <vector>
#include "Ball.h"	
#include "Level.h"
#include "Player.h"

class Balls
{
public:
	Balls();
	Balls(SDL_Rect src, float scale, float y);
	~Balls();

	void addBall();
	void update(float dt, Level& level, Player player, float margin);
	void draw();

	int deathCounter = 0;
	std::vector<Ball> balls;

private:
	float shootRate = 0.2f;
	float shootTimer = shootRate;

	float scale = 0;
	float spawnY = 0;
	SDL_Rect src{ 0, 0, 0, 0 };

	void tryShoot(float dt);
	void checkLose(Ball& ball, int i, int x);
	void collide(Player& player, Ball& ball, float dt);
};

