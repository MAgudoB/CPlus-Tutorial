#include "pch.h"
#include "Particle.h"
#include <math.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <cmath>

Particle::Particle(): sdl_x(0),sdl_y(0) {
	sdl_direction = (2 * M_PI * rand()) / RAND_MAX;
	sdl_speed = (0.0001 * rand()) / RAND_MAX;
}

Particle::~Particle() {
}

void Particle::update(int interval) {

	//sdl_direction += interval * 0.004;

	double x_speed = sdl_speed * cos(sdl_direction);
	double y_speed = sdl_speed * sin(sdl_direction);

	sdl_x += x_speed * interval;
	sdl_y += y_speed * interval;
}