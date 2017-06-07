#pragma once

#include <vector>

#include <Box2D\Box2D.h>
#include <Engine\IGameScreen.h>
#include <Engine\Window.h>
#include <Engine\GLSLProgram.h>
#include <Engine\Camera2D.h>
#include <Engine\SpriteBatch.h>
#include <Engine\SpriteFont.h>
#include <Engine\Vertex.h>
#include <Engine\DebugRenderer.h>
#include <Engine\GLTexture.h>

#include "Player_Clung.h"
#include "MedKit_Clung.h"
#include "Listener_Contact_Clung.h"

#define DEBUG 1

class Screen_GP_Clung : public Engine::IGameScreen
{
public:
	Screen_GP_Clung(Engine::Window* window);
	~Screen_GP_Clung();

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
	void renderGUI(glm::mat4& projectionMatrix);
	void renderDebug(glm::mat4& projectionMatrix);
	void renderDebugText(glm::mat4& projectionMatrix);

	Engine::GLSLProgram m_textureProgram;
	Engine::Camera2D m_camera;
	Engine::Camera2D m_displayCamera;
	Engine::SpriteBatch m_spriteBatch;
	Engine::SpriteBatch m_textSpriteBatch;
	Engine::SpriteFont* m_spriteFont;
	Engine::GLTexture m_texture;
	Engine::Window* m_window;
	Engine::DebugRenderer m_debugRenderer;

	std::unique_ptr<b2World> m_world;

	Player_Clung* m_player;
	std::vector<Entity_Clung*> m_entities;
	std::vector<Entity_Clung*> m_items;

	bool m_debug = DEBUG;
	int m_currentLevel = 0;

	Listener_Contact_Clung m_contactListener;
};

