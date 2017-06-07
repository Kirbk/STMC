#pragma once
#include <SDL.h>
#include <glew.h>
#include <string>

namespace Engine {
	enum WindowFlags { HIDDEN = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4, RESIZABLE = 0x8};

	class Window
	{
	public:
		Window();
		~Window();

		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags = 0);

		void swapBuffer();

		int getScreenWidth() { return _screenWidth; }
		int getScreenHeight() { return _screenHeight; }
	private:
		SDL_Window* _sdlWindow;
		int _screenWidth, _screenHeight;
	};

}