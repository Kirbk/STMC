#pragma once

#include <Engine\IMainGame.h>

#include "Screen_GP_Pong.h"

class App_Pong : public Engine::IMainGame
{
public:
	App_Pong();
	~App_Pong();

	// Inherited via IMainGame
	virtual void onInit() override;
	virtual void addScreens() override;
	virtual void onExit() override;

private:
	std::unique_ptr<Screen_GP_Pong> m_gameplayScreen = nullptr;
};

