#pragma once

#include "Particle.h"

class Swarm
{
private:
	Particle *m_ptrParticle;

public:
	int NB_PARTICLES;
	
	Swarm(int n);
	~Swarm();

	Particle * const getParticles() { return m_ptrParticle; }
	void update();
};