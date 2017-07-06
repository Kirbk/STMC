#include "Screen_GP_Pong.h"

#include <Engine\IMainGame.h>

#include <Engine\ResourceManager.h>

#include <iostream>

Screen_GP_Pong::Screen_GP_Pong(Engine::Window* window) : m_window(window)
{
}


Screen_GP_Pong::~Screen_GP_Pong()
{
}

int Screen_GP_Pong::getNextScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

int Screen_GP_Pong::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

void Screen_GP_Pong::build()
{
}

void Screen_GP_Pong::destroy()
{
}

void Screen_GP_Pong::onEntry()
{
	m_world = std::make_unique<b2World>(b2Vec2(0.0f, 0.0f));
	m_world.get()->SetContactListener(&m_contactListener);

	m_debugRenderer.init();

	// Initialize SpriteBatch
	m_spriteBatch.init();
	m_textSpriteBatch.init();

	m_spriteFont = new Engine::SpriteFont("Assets/fonts/Oswald-SemiBold.ttf", 64);

	// Shader init
	m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/fragmentShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();

	// Init camera
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setScale(1.0f);

	m_displayCamera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_displayCamera.setPosition(glm::vec2(m_window->getScreenWidth() / 2, m_window->getScreenHeight() / 2));

	m_paddle1.init(m_world.get(), glm::vec2(-6.25f, 0), glm::vec2(12.5f, 50.0f), Engine::ColorRGBA8(255, 255, 255, 255), 0);
	m_paddle2.init(m_world.get(), glm::vec2(6.25f, 0), glm::vec2(12.5f, 50.0f), Engine::ColorRGBA8(255, 255, 255, 255), 1);
	m_ball.init(m_world.get(), glm::vec2(30.0f, 0.0f), glm::vec2(20.0f, 20.0f), glm::vec2(m_window->getScreenWidth(), m_window->getScreenHeight()), Engine::ColorRGBA8(255, 255, 255, 255), 100);
	m_border.init(m_world.get(), glm::vec2(0, 0), glm::vec2(100.0f, m_window->getScreenHeight()), Engine::ColorRGBA8(255, 255, 255, 255));
}

void Screen_GP_Pong::onExit()
{
}

void Screen_GP_Pong::update()
{
	m_camera.update();
	m_displayCamera.update();

	m_paddle1.update(m_game->inputManager);
	m_paddle2.update(m_game->inputManager);
	m_ball.update();

	checkInput();

	m_world->Step(1.0f / 60.0f, 6, 2);
}

void Screen_GP_Pong::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.8f, 0.4f, 1.0f);

	m_textureProgram.use();

	// Upload texture uniform
	GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	// Camera matrix
	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	GLint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_spriteBatch.begin();

	
	m_border.draw(m_spriteBatch);
	m_paddle1.draw(m_spriteBatch);
	m_paddle2.draw(m_spriteBatch);
	m_ball.draw(m_spriteBatch);
	

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_textureProgram.unuse();

	renderGUI(projectionMatrix);
}

void Screen_GP_Pong::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);
	}
}

void Screen_GP_Pong::renderGUI(glm::mat4 & projectionMatrix)
{
	m_textureProgram.use();

	glm::mat4 textProjectionMatrix = m_displayCamera.getCameraMatrix();
	GLint textpUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(textpUniform, 1, GL_FALSE, &textProjectionMatrix[0][0]);

	m_textSpriteBatch.begin();

	char buffer[256];
	sprintf_s(buffer, "%i", m_paddle1.getScore());
	m_spriteFont->draw(m_textSpriteBatch, buffer, glm::vec2(5.0f, 0.0f), glm::vec2(0.4f), 0.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	m_textSpriteBatch.end();
	m_textSpriteBatch.renderBatch();
	m_textureProgram.unuse();
}
