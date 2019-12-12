#pragma once

#ifndef FIRE_H
#define FIRE_H

#include "SDL.h"

class FireParticle {
private:
	SDL_Window * sdlWindow;
	SDL_Renderer *sdlRenderer;
	SDL_Texture *sdlTexture;
	Uint32 *sdlBuffer1;
	Uint32 *sdlBuffer2;
public:
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;
	FireParticle();
	bool init();
	void update();
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	bool processEvent();
	void close();
	void clear();
	void boxBlur();
};

#endif FIRE_H