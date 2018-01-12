#include "Particle.h"
#include <random>
#include <math.h>

void Particle::init()
{
	m_x = 0.0f;
	m_y = 0.0f;

	m_rSpeed = (0.04f*rand()) / RAND_MAX;
	m_rSpeed *= m_rSpeed;

	m_angle = (float)(2.0f*PI*rand()) / RAND_MAX;
	m_angleSpeed = 0.001f;
}
Particle::Particle()
	: m_r(0xff), m_g(0xff), m_b(0xff)
{
	init();
}

void Particle::move()
{
	m_angle += m_angleSpeed;

	m_x += m_rSpeed*cos(m_angle);
	m_y += m_rSpeed*sin(m_angle);

	if (m_x<-1.0f || m_x>1.0f || m_y<-1.0f || m_y>1.0f)
		init();
}

void Particle::move(int interval)
{
	m_angle += m_angleSpeed;

	m_x += m_rSpeed*cos(m_angle) * interval;
	m_y += m_rSpeed*sin(m_angle) * interval;

	if (m_x<-1.0f || m_x>1.0f || m_y<-1.0f || m_y>1.0f)
		init();

}



