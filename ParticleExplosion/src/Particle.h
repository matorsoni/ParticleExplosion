#pragma once

#include "SDL.h"

class Particle
{
private:
	float m_xSpeed;
	float m_ySpeed;

	//0xrrggbbaa
	Uint8 m_r;
	Uint8 m_g;
	Uint8 m_b;

	
	

public:
	
	//-1.0 <= x, y <= 1.0
	//maybe use double instead of float, for the sake of precision?
	float m_x;
	float m_y;

	Particle();
	Particle(Uint8 r, Uint8 g, Uint8 b);
	Particle(float x, float y, Uint8 r, Uint8 g, Uint8 b);

	Uint8 getRed() { return m_r; }
	Uint8 getGreen() { return m_g; }
	Uint8 getBlue() { return m_b; }

	void move();






};