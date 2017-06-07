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
}

void App_Clung::addScreens()
{
	m_gameplayScreen = std::make_unique<Screen_GP_Clung>(&m_window);
	m_screenList->addScreen(m_gameplayScreen.get());
	m_screenList->setScreen(m_gameplayScreen->getScreenIndex());
}

void App_Clung::onExit()
{
}
