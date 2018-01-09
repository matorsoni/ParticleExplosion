#include "Particle.h"
#include <random>
#include <math.h>


Particle::Particle()
	: m_r(0xff), m_g(0xff), m_b(0xff)
{
	/*
	m_x = (float)rand() * 2 / RAND_MAX - 1;
	m_y = (float)rand() * 2 / RAND_MAX - 1;
	*/

	m_x = 0.0f;
	m_y = 0.0f;

	m_rSpeed = (float)(0.0001f*rand()) / RAND_MAX;
	m_angle = (float)(2.0f*PI*rand()) / RAND_MAX;
	m_angleSpeed = 0.001f;
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

void Particle::move(int interval)
{
	float r = sqrt(m_x*m_x + m_y*m_y);
	m_x += (m_rSpeed*cos(m_angle) - r*sin(m_angle)*m_angleSpeed) * interval;
	m_y += (m_rSpeed*sin(m_angle) + r*cos(m_angle)*m_angleSpeed) * interval;
}
/////

