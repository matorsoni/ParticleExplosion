#include "Particle.h"
#include <random>


Particle::Particle()
	: m_r(0xff), m_g(0xff), m_b(0xff)
{
	/*
	m_x = (float)rand() * 2 / RAND_MAX - 1;
	m_y = (float)rand() * 2 / RAND_MAX - 1;
	*/

	m_x = 0.0f;
	m_y = 0.0f;

	m_xSpeed = (float)0.01f*(rand() * 2.0f / RAND_MAX - 1.0f);
	m_ySpeed = (float)0.01f*(rand() * 2.0f / RAND_MAX - 1.0f);

}

Particle::Particle(Uint8 r, Uint8 g, Uint8 b)
	: m_r(r), m_g(g), m_b(b)
{
	m_x = (float)rand() * 2 / RAND_MAX - 1;
	m_y = (float)rand() * 2 / RAND_MAX - 1;
}

Particle::Particle(float x, float y, Uint8 r, Uint8 g, Uint8 b)
	: m_x(x), m_y(y), m_r(r), m_g(g), m_b(b)
{}

void Particle::move()
{
	//bouncing
	if (m_x<-1.0 || m_x>1.0)
		m_xSpeed = -m_xSpeed;
	if (m_y<-1.0 || m_y>1.0)
		m_ySpeed = -m_ySpeed;

	m_x += m_xSpeed;
	m_y += m_ySpeed;
}
/////

