#pragma once

#include <Engine\IMainGame.h>

#include "Screen_GP_Clung.h"

class App_Clung : public Engine::IMainGame
{
public:
	App_Clung();
	~App_Clung();

	virtual void onInit() override;
	virtual void addScreens() override;
	virtual void onExit() override;

private:
	std::unique_ptr<Screen_GP_Clung> m_gameplayScreen = nullptr;
};

