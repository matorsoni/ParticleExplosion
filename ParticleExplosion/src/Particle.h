#pragma once

#include "SDL.h"


class Particle
{
private:
	float m_rSpeed;
	float m_angle;
	float m_angleSpeed;
	//0xrrggbbaa
	Uint8 m_r;
	Uint8 m_g;
	Uint8 m_b;

	void init();
	

public:
	const float PI = 3.14159f;
	//-1.0 <= x, y <= 1.0
	//maybe use double instead of float, for the sake of precision?
	float m_x;
	float m_y;

	Particle();

	Uint8 getRed() { return m_r; }
	Uint8 getGreen() { return m_g; }
	Uint8 getBlue() { return m_b; }
	
	//using interval between loops to insure constante frame rates
	void move();
	void move(int interval);






};