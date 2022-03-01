#pragma once

//
//SDL_Texture* loadTexture(const char* fileName);
//void setTexture(const char* fileName);

struct SDL_Texture;
struct SDL_Rect;

namespace engine
{
	void init();
	void render();
	void drawTexture(SDL_Texture* texture, SDL_Rect src, SDL_Rect dst);
	SDL_Texture* loadTexture(const char* path);

	void present();
	void close();
}
