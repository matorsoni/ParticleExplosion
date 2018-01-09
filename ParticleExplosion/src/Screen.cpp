#pragma once

#include "Screen.h"
#include <iostream>

Screen::Screen(const int w, const int h)
	: WIDTH(w), HEIGHT(h)
{
	if (!init())
		SDL_Quit();
}

Screen::~Screen()
{
	delete[] m_buffer;
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

bool Screen::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL_init Failed" << std::endl;
		return false;
	}

	m_window = SDL_CreateWindow("Particle Explosion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	if (m_window == NULL)
	{
		std::cout << "window failed" << std::endl;
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (m_renderer == NULL)
	{
		std::cout << "renderer failed" << std::endl;
		SDL_DestroyWindow(m_window);
		return false;
	}

	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);

	if (m_texture == NULL)
	{
		std::cout << "texture failed" << std::endl;
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		return false;
	}

	m_buffer = new Uint32[WIDTH*HEIGHT];

	//black screen
	memset(m_buffer, 0x00000000, WIDTH*HEIGHT*sizeof(Uint32));
	

	return true;
}

void Screen::update()
{
	//updates screen
	SDL_UpdateTexture(m_texture, NULL, m_buffer, 800 * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
{
	if (x<0 || x>WIDTH - 1 || y<0 || y>HEIGHT - 1)
		return;

	Uint32 pixel = 0x00000000;

	pixel += red;
	pixel <<= 8;
	pixel += green;
	pixel <<= 8;
	pixel += blue;
	pixel <<= 8;
	pixel += 0xff; //alpha = 255 always in this project

	m_buffer[(WIDTH*y) + x] = pixel;
}

void Screen::setPixel(Particle part)
{
	int x = (int)((part.m_x + 1)*WIDTH / 2);
	int y = (int)((HEIGHT - (part.m_y + 1)*HEIGHT / 2));
	Uint8 red = part.getRed();
	Uint8 green = part.getGreen();
	Uint8 blue = part.getBlue();

	setPixel(x, y, red, green, blue);
}

void Screen::setPixel(Particle part, Uint8 red, Uint8 green, Uint8 blue)
{
	int x = (int)((part.m_x + 1.0f)*WIDTH / 2);
	int y = (int)(HEIGHT - (part.m_y/HEIGHT*WIDTH + 1.0f)*HEIGHT / 2); //scales y to the same scale as x

	setPixel(x, y, red, green, blue);
}

void Screen::clear()
{
	memset(m_buffer, 0x00000000, WIDTH * HEIGHT * sizeof(Uint32));
}



