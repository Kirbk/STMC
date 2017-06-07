#pragma once

#include <Box2D\Box2D.h>
#include <Engine\IGameScreen.h>
#include <Engine\SpriteBatch.h>
#include <Engine\GLSLProgram.h>
#include <Engine\Camera2D.h>
#include <Engine\GLTexture.h>
#include <Engine\Window.h>
#include <Engine\DebugRenderer.h>
#include <Engine\SpriteFont.h>
#include <Engine\GUI.h>
#include <vector>
#include "Box.h"
#include "Player.h"

class GameplayScreen : public Engine::IGameScreen
{
public:
	GameplayScreen(Engine::Window* window);
	~GameplayScreen();

	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;

	// Called at beginning and end of application
	virtual void build() override;
	virtual void destroy() override;

	// Called when a screen enters and exits focus
	virtual void onEntry() override;
	virtual void onExit() override;

	// Called in the main game loop
	virtual void update() override;
	virtual void draw() override;

private:
	void initUI();
	void checkInput();
	void renderDebug(glm::mat4& projectionMatrix);

	bool onExitClicked(const CEGUI::EventArgs& e);

	Engine::GLSLProgram m_textureProgram;
	Engine::GLSLProgram m_lightProgram;
	Engine::Camera2D m_camera;
	Engine::SpriteBatch m_spriteBatch;
	Engine::SpriteBatch m_debugTextSpriteBatch;
	Engine::SpriteFont* m_spriteFont;
	Engine::GLTexture m_texture;
	Engine::Window* m_window;
	Engine::DebugRenderer m_debugRenderer;
	Engine::GUI m_gui;

	bool m_debug = false;

	Player m_player;

	std::vector<Box> m_boxes;
	std::unique_ptr<b2World> m_world;
};

