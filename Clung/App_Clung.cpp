#include "App_Clung.h"

#include <Engine\ScreenList.h>


App_Clung::App_Clung()
{
	m_width = 1024;
	m_height = 768;
	m_windowName = "Clung";
}


App_Clung::~App_Clung()
{
}

void App_Clung::onInit()
{
	SDL_JoystickEventState(SDL_ENABLE);
}

void App_Clung::addScreens()
{
	m_mainMenuScreen = std::make_unique<Screen_Start_Clung>(&m_window);
	m_gameplayScreen = std::make_unique<Screen_GP_Clung>(&m_window);

	m_screenList->addScreen(m_mainMenuScreen.get());
	m_screenList->addScreen(m_gameplayScreen.get());

	m_screenList->setScreen(m_mainMenuScreen->getScreenIndex());
}

void App_Clung::onExit()
{
}
