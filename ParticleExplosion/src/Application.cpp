#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Screen.h"
#include "Swarm.h"


//ou int argc, char *argv[]
int main(int argc, char **argv)
{
	Screen screen(800, 600);

	//allows different random numbers each time it runs
	srand(time(NULL));
	
	bool quit = false;
	SDL_Event event;

	//number of particles
	Swarm swarm(5000);
	Particle *ptr = swarm.getParticles();

	//oscillating colors
	unsigned char red;
	unsigned char green;
	unsigned char blue;

	//color oscillation frequency 
	const float RED_FREQ = 0.001f;
	const float GREEN_FREQ = 0.0005f;
	const float BLUE_FREQ = 0.0015f;

	int last_time = 0;

	bool blur_on = false;

	//game loop
	while (!quit)
	{
		int time_elapsed = SDL_GetTicks();

		//varying colors
		red = (unsigned char)((1 + sin(time_elapsed * RED_FREQ)) * 127);
		green = (unsigned char)((1 + sin(time_elapsed * GREEN_FREQ)) * 127);
		blue = (unsigned char)((1 + sin(time_elapsed * BLUE_FREQ)) * 127);

		//show particles with varying rgb and position
		for (int i = 0; i <swarm.NB_PARTICLES; i++)
		{
			ptr[i].move(time_elapsed - last_time);
			screen.setPixel(ptr[i], red, green, blue);
		}

		last_time = time_elapsed;

		if(blur_on)
			screen.boxBlur();

		screen.update();
		
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
		}

		screen.clear(blur_on);
	}
			
	return 0;

}