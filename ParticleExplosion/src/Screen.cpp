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
	delete[] m_bufferBlur;
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
	m_bufferBlur = new Uint32[WIDTH*HEIGHT];

	//black screen
	memset(m_buffer, 0x00000000, WIDTH*HEIGHT*sizeof(Uint32));
	memset(m_bufferBlur, 0x00000000, WIDTH*HEIGHT * sizeof(Uint32));
	

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
	int x = (int)((part.m_x + 1.0f)*WIDTH / 2);
	int y = (int)(HEIGHT - (part.m_y / HEIGHT*WIDTH + 1.0f)*HEIGHT / 2); //scales y to the same scale as x
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

void Screen::clear(bool blur_on)
{
	if(!blur_on)
		memset(m_buffer, 0x00000000, WIDTH * HEIGHT * sizeof(Uint32));
}

void Screen::boxBlur()
{
	//calculates the average of each color of one pixel and the 8 pixels surrounding it
	Uint32 *aux = m_buffer;
	m_buffer = m_bufferBlur;
	m_bufferBlur = aux;

	int posX;
	int posY;

	Uint8 red, blue, green;
	Uint32 buffer_pixel, blur_pixel;
	int pixel_counter;

	//loop throug the whole m_buffer
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
		{
			pixel_counter = 0;
			red = 0;
			green = 0;
			blue = 0;

			blur_pixel = 0x00000000;

			//loop through the 9 pixel grid for each pixel from m_buffer
			for (int i = -1; i < 2; i++)
				for (int j = -1; j < 2; j++)
				{
					posX = x + j;
					posY = y + i;
					

					if (posX >= 0 && posX < WIDTH && posY >= 0 && posY < HEIGHT)
					{
						buffer_pixel = m_bufferBlur[posY*WIDTH + posX];
						
						red += getRed(buffer_pixel);
						green += getGreen(buffer_pixel);
						blue += getBlue(buffer_pixel);

						pixel_counter++;
					}

				}

			if (pixel_counter == 0)
				continue;

			Uint8 aux = (red > blue) ? red : blue;
			Uint8 max_color = (aux > green) ? aux : green;

			if (max_color == 0)
				continue;

		//  deixar as cores mais claras e bonitas

		//	red = red * 255 /(max_color * pixel_counter);
		//	green = green * 255 / (max_color * pixel_counter);
		//	blue = blue * 255 / (max_color * pixel_counter);

			red /= 9;
			green /= 9;
			blue /= 9;

			setPixel(x, y, red, green, blue);
		}

	
	
}

Uint8 Screen::getRed(Uint32 pixel)
{
	Uint8 red = pixel>>24;
	return red;
}

Uint8 Screen::getGreen(Uint32 pixel)
{
	Uint8 green = pixel >> 16;
	return green;
}

Uint8 Screen::getBlue(Uint32 pixel)
{
	Uint8 blue = pixel >> 8;
	return blue;
}