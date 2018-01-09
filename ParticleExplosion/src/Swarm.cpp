#include "Swarm.h"

Swarm::Swarm(int n)
{
	NB_PARTICLES = n;
	m_ptrParticle = new Particle[NB_PARTICLES];

}

Swarm::~Swarm()
{
	delete[] m_ptrParticle;
}

void Swarm::update()
{

}
