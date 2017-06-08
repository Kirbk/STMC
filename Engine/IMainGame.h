#pragma once

#include <memory>
#include "Engine.h"
#include "Window.h"
#include "InputManager.h"

namespace Engine{

	class ScreenList;
	class IGameScreen;

	class IMainGame
	{
	public:
		IMainGame();
		virtual ~IMainGame();

		void run();
		void exitGame();

		virtual void onInit() = 0;
		virtual void addScreens() = 0;
		virtual void onExit() = 0;

		void onSDLEvent(SDL_Event& evnt);

		const float getFps() const { return m_fps; }

		InputManager inputManager;

	protected:
		virtual void update();
		virtual void draw();

		bool init();
		bool initSystems();

		std::unique_ptr<ScreenList> m_screenList = nullptr;
		IGameScreen* m_currentScreen = nullptr;
		bool m_isRunning = false;
		float m_fps;
		float m_height = 1024, m_width = 768;
		std::string m_windowName = "DEFAULT";
		unsigned int m_windowFlags = 0;
		Window m_window;
	};

}