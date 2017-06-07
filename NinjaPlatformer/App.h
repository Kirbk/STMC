#pragma once

#include <Engine\IMainGame.h>
#include "GameplayScreen.h"
#include "MainMenuScreen.h"

class App : public Engine::IMainGame
{
public:
	App();
	~App();

	virtual void onInit() override;
	virtual void addScreens() override;
	virtual void onExit() override;

private:
	std::unique_ptr<GameplayScreen> m_gameplayScreen = nullptr;
	std::unique_ptr<MainMenuScreen> m_mainMenuScreen = nullptr;
};

