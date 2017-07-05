#include "App_Pong.h"

#include <Engine\ScreenList.h>

App_Pong::App_Pong()
{
	m_width = 640;
	m_height = 480;
	m_windowName = "Pong";
}


App_Pong::~App_Pong()
{
}

void App_Pong::onInit()
{

}

void App_Pong::addScreens()
{
	m_gameplayScreen = std::make_unique<Screen_GP_Pong>(&m_window);

	m_screenList->addScreen(m_gameplayScreen.get());
	m_screenList->setScreen(m_gameplayScreen.get()->getScreenIndex());
}

void App_Pong::onExit()
{
}
