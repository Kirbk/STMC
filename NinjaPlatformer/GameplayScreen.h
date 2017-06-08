#pragma once

#include "Box.h"
#include "Player.h"
#include <Engine/IGameScreen.h>
#include <Box2D/Box2D.h>
#include <vector>
#include <Engine/SpriteBatch.h>
#include <Engine/GLSLProgram.h>
#include <Engine/Camera2D.h>
#include <Engine/GLTexture.h>
#include <Engine/Window.h>
#include <Engine/DebugRenderer.h>

#include <Engine/GUI.h>

// Our custom gameplay screen that inherits from the IGameScreen
class GameplayScreen : public Engine::IGameScreen {
public:
	GameplayScreen(Engine::Window* window);
	~GameplayScreen();

	virtual int getNextScreenIndex() const override;

	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;

	virtual void destroy() override;

	virtual void onEntry() override;

	virtual void onExit() override;

	virtual void update() override;

	virtual void draw() override;

private:
	void initUI();
	void checkInput();

	bool onExitClicked(const CEGUI::EventArgs& e);

	Engine::SpriteBatch m_spriteBatch;
	Engine::GLSLProgram m_textureProgram;
	Engine::GLSLProgram m_lightProgram;
	Engine::Camera2D m_camera;
	Engine::GLTexture m_texture;
	Engine::Window* m_window;
	Engine::DebugRenderer m_debugRenderer;
	Engine::GUI m_gui;

	bool m_renderDebug = false;

	Player m_player;
	std::vector<Box> m_boxes;
	std::unique_ptr<b2World> m_world;
};

