#include "pch.h"
#include "FireParticle.h"
#include <iostream>

FireParticle::FireParticle(): sdlWindow(NULL),sdlRenderer(NULL),sdlTexture(NULL),sdlBuffer1(NULL) {
	
}




bool FireParticle::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}

	sdlWindow = SDL_CreateWindow("Particle Explosion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (sdlWindow == NULL) {
		SDL_Quit();
		return false;
	}

	sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	sdlTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

	if (sdlRenderer == NULL) {
		SDL_DestroyTexture(sdlTexture);
		SDL_DestroyWindow(sdlWindow);
		SDL_Quit();
		return false;
	}

	if (sdlTexture == NULL) {
		SDL_DestroyRenderer(sdlRenderer);
		SDL_DestroyWindow(sdlWindow);
		SDL_Quit();
		return false;
	}

	sdlBuffer1 = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];

	memset(sdlBuffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

	sdlBuffer2 = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];

	memset(sdlBuffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		sdlBuffer1[i] = 0xFFFFFFFF;
	}

	return true;
}

void FireParticle::update() {
	SDL_UpdateTexture(sdlTexture, NULL, sdlBuffer1, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(sdlRenderer);
	SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
	SDL_RenderPresent(sdlRenderer);
}

void FireParticle::clear() {
	memset(sdlBuffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
}

void FireParticle::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return;

	Uint32 color = 0;

	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += 0xFF;

	sdlBuffer1[(y* SCREEN_WIDTH) + x] = color;

}

bool FireParticle::processEvent() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return false;
		}
	}
	return true;
}

void FireParticle::close() {
	delete[] sdlBuffer1;
	delete[] sdlBuffer2;
	SDL_DestroyTexture(sdlTexture);
	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
}

void FireParticle::boxBlur()	{
	Uint32 * tempBuff = sdlBuffer1;
	sdlBuffer1 = sdlBuffer2;
	sdlBuffer2 = tempBuff;

	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;

			for (int row = -1; row <= 1; row++) {
				for (int col = -1; col <= 1; col++) {
					int currentX = x + col;
					int currentY = y + row;

					if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT) {
						Uint32 color = sdlBuffer2[currentY*SCREEN_WIDTH + currentX];

						Uint8 red = color >> 24;
						Uint8 green = color >> 16;
						Uint8 blue = color >> 8;

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;
					}
				}
			}

			Uint8 red = redTotal / 9;
			Uint8 green = greenTotal / 9;
			Uint8 blue = blueTotal / 9;

			setPixel(x, y, red, green, blue);

		}
	}

}