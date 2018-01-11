#pragma once

#include <string>
#include "SDL.h"

#include "Particle.h"

class Screen
{
private:
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;

	//buffer that contains the particles and auxiliary buffer
	//to calculate blur effect.
	Uint32 *m_buffer;
	Uint32 *m_bufferBlur;

	bool init();

public:
	const int WIDTH;
	const int HEIGHT;

	Screen(int w, int h);
	~Screen();

	void update();
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	void clear(bool blur_on);

	//not general methods
	void setPixel(Particle part);
	void setPixel(Particle part, Uint8 red, Uint8 green, Uint8 blue);
	void boxBlur();

	Uint8 getRed(Uint32 pixel);
	Uint8 getGreen(Uint32 pixel);
	Uint8 getBlue(Uint32 pixel);
	

};