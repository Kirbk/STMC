#include <SDl.h>
#include <glew.h>
#include <iostream>
#include "Engine.h"

namespace Engine {

	int init() {
		//Initialize SDL
		SDL_Init(SDL_INIT_VIDEO);
		SDL_Init(SDL_INIT_EVENTS);
		SDL_Init(SDL_INIT_TIMER);
		SDL_Init(SDL_INIT_GAMECONTROLLER);
		SDL_Init(SDL_INIT_JOYSTICK);
		SDL_Init(SDL_INIT_NOPARACHUTE);

		//Tell SDL that we want a double buffered window so we dont get
		//any flickering
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}
}