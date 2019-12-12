#pragma once

#include "Particle.h";

#define _SWARM_
#ifdef _SWARM_
class Swarm {
public:
	const static int NPARTICLES = 5000;
private:
	Particle * sdl_pParticles;
	int lastTime;
public:
	Swarm();
	virtual ~Swarm();
	void update(int interval);
	const Particle * const getParticles() { return sdl_pParticles; };
};

#endif // _SWARM_
