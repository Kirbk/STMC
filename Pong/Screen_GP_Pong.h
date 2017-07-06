#pragma once

#include <Engine\IGameScreen.h>
#include <Engine\Window.h>
#include <Engine\GLSLProgram.h>
#include <Engine\Camera2D.h>
#include <Engine\SpriteBatch.h>
#include <Engine\SpriteFont.h>
#include <Engine\DebugRenderer.h>

#include <Box2D\Box2D.h>

#include "Paddle_Pong.h"
#include "Ball_Pong.h"
#include "Border_Pong.h"
#include "Contact_Listener_Pong.h"

class Screen_GP_Pong : public Engine::IGameScreen
{
public:
	Screen_GP_Pong(Engine::Window* window);
	~Screen_GP_Pong();

	// Inherited via IGameScreen
	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;
	virtual void build() override;
	virtual void destroy() override;
	virtual void onEntry() override;
	virtual void onExit() override;
	virtual void update() override;
	virtual void draw() override;

private:
	void checkInput();
	void renderGUI(glm::mat4 & projectionMatrix);

	Engine::GLSLProgram m_textureProgram;
	Engine::Camera2D m_camera;
	Engine::Camera2D m_displayCamera;
	Engine::SpriteBatch m_spriteBatch;
	Engine::SpriteBatch m_textSpriteBatch;
	Engine::SpriteFont* m_spriteFont;
	Engine::Window* m_window;
	Engine::DebugRenderer m_debugRenderer;
	Contact_Listener_Pong m_contactListener;

	std::unique_ptr<b2World> m_world;

	Paddle_Pong m_paddle1;
	Paddle_Pong m_paddle2;
	Ball_Pong m_ball;
	Border_Pong m_border;
};
