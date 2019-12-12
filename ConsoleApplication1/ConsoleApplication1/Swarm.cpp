#include "pch.h"
#include "Swarm.h"
#include <stdlib.h>

Swarm::Swarm(): lastTime(0) {
	sdl_pParticles = new Particle[NPARTICLES];
}

Swarm::~Swarm() {
	delete [] sdl_pParticles;
}

void Swarm::update(int elapsed) {

	int interval = elapsed - lastTime;

	for (int i = 0; i < Swarm::NPARTICLES; i++) {

		sdl_pParticles[i].update(interval);
	}
	lastTime = elapsed;
}