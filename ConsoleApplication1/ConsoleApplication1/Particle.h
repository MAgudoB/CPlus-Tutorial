#pragma once

#define _PARTICLE_
#ifdef _PARTICLE_


class Particle {
public:
	double sdl_x;
	double sdl_y;
	
	double sdl_speed;
	double sdl_direction;

public:
	Particle();
	~Particle();
	void update(int interval);
};

#endif // _PARTICLE_
