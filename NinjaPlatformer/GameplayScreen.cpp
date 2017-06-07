#include "GameplayScreen.h"
#include <iostream>
#include <SDL.h>
#include <Engine\IMainGame.h>
#include <Engine\ResourceManager.h>
#include <random>

#include "Light.h"
#include "ScreenIndices.h"


GameplayScreen::GameplayScreen(Engine::Window* window) : m_window(window)
{
	m_screenIndex = SCREEN_INDEX_GAMEPLAY;
}


GameplayScreen::~GameplayScreen()
{
}

int GameplayScreen::getNextScreenIndex() const {
	return SCREEN_INDEX_NO_SCREEN;
}

int GameplayScreen::getPreviousScreenIndex() const {
	return SCREEN_INDEX_MAINMENU;
}

// Called at beginning and end of application
void GameplayScreen::build() {

}

void GameplayScreen::destroy() {

}

// Called when a screen enters and exits focus
void GameplayScreen::onEntry() {
	

	b2Vec2 gravity(0.0f, -20.0f);
	m_world = std::make_unique<b2World>(gravity);

	m_debugRenderer.init();

	// Make the ground
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -25.0f);
	b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

	// Make the ground fixture
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Load the texture
	m_texture = Engine::ResourceManager::getTexture("Assets/textures/block.png");

	std::mt19937 randGenerator;
	std::uniform_real_distribution<float> xPos(-10.0f, 10.0f);
	std::uniform_real_distribution<float> yPos(-10.0f, 15.0f);
	std::uniform_real_distribution<float> size(0.5f, 2.5f);
	std::uniform_int_distribution<int> color(0, 255);
	const int NUM_BOXES = 10;

	for (int i = 0; i < NUM_BOXES; i++) {
		Engine::ColorRGBA8 randColor;
		randColor.r = color(randGenerator);
		randColor.g = color(randGenerator);
		randColor.b = color(randGenerator);
		randColor.a = 255;


		Box newBox;
		float s = size(randGenerator);
		newBox.init(m_world.get(), glm::vec2(xPos(randGenerator), yPos(randGenerator)), glm::vec2(s, s), m_texture, randColor);

		m_boxes.push_back(newBox);
	}

	// Initialize SpriteBatch
	m_spriteBatch.init();
	m_debugTextSpriteBatch.init();

	m_spriteFont = new Engine::SpriteFont("Assets/fonts/Oswald-SemiBold.ttf", 64);

	// Shader init
	m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();

	m_lightProgram.compileShaders("Shaders/lightShading.vert", "Shaders/lightShading.frag");
	m_lightProgram.addAttribute("vertexPosition");
	m_lightProgram.addAttribute("vertexColor");
	m_lightProgram.addAttribute("vertexUV");
	m_lightProgram.linkShaders();

	// Init camera
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setScale(25.0f);

	// Init player
	m_player.init(m_world.get(), glm::vec2(0.0f, 30.0f), glm::vec2(2.0f), glm::vec2(1.0f, 1.8f), Engine::ColorRGBA8(255, 255, 255, 255));

	initUI();
}

void GameplayScreen::onExit() {
	m_debugRenderer.dispose();
}

// Called in the main game loop
void GameplayScreen::update() {
	m_camera.update();
	checkInput();

	m_player.update(m_game->inputManager);
	
	for (Box& b : m_boxes) {
		b.update(m_game->inputManager, m_camera);
	}

	// Update physics
	m_world->Step(1.0f / 60.0f, 32, 16);
}

void GameplayScreen::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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

	for (auto& b : m_boxes) {
		b.draw(m_spriteBatch);
	}

	m_player.draw(m_spriteBatch);

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_textureProgram.unuse();

	if (m_debug) renderDebug(projectionMatrix);

	Light playerLight;
	playerLight.color = Engine::ColorRGBA8(255, 255, 255, 128);
	playerLight.position = m_player.getPosition();
	playerLight.size = 30.0f;

	Light mouseLight;
	mouseLight.color = Engine::ColorRGBA8(255, 0, 255, 150);
	mouseLight.position = m_camera.convertScreenToWorld(m_game->inputManager.getMouseCoords());
	mouseLight.size = 45.0f;

	m_lightProgram.use();

	pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	m_spriteBatch.begin();

	playerLight.draw(m_spriteBatch);
	mouseLight.draw(m_spriteBatch);

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	m_lightProgram.unuse();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_gui.draw();
}

void GameplayScreen::initUI()
{
	m_gui.init("GUI");
	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.loadScheme("AlfiskoSkin.scheme");
	m_gui.setFont("DejaVuSans-10");
	CEGUI::PushButton* testButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("AlfiskoSkin/Button", glm::vec4(0.5f, 0.5f, 0.1f, 0.05f), glm::vec4(0), "TestButton"));
	testButton->setText("Exit Game!");

	testButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameplayScreen::onExitClicked, this));

	CEGUI::Combobox* testCombobox = static_cast<CEGUI::Combobox*>(m_gui.createWidget("TaharezLook/Combobox", glm::vec4(0.2f, 0.2f, 0.1f, 0.05f), glm::vec4(0), "TestComboBox"));

	m_gui.setMouseCursor("AlfiskoSkin/MouseArrow");
	m_gui.showMouseCursor();
	SDL_ShowCursor(false);
}

void GameplayScreen::checkInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);

		m_gui.onSDLEvent(evnt);

		if (evnt.type == SDL_JOYBUTTONDOWN) {
			if (evnt.jbutton.button == 0) {
				std::cout << "asdf\n";
			}
		}
	}

	if (m_game->inputManager.isKeyPressed(SDLK_F8)) {
		m_debug = !m_debug;
	}
}

void GameplayScreen::renderDebug(glm::mat4& projectionMatrix) {
	glm::vec4 destRect;
	for (auto& b : m_boxes) {
		destRect.x = b.getBody()->GetPosition().x - b.getDimensions().x / 2;
		destRect.y = b.getBody()->GetPosition().y - b.getDimensions().y / 2;
		destRect.z = b.getDimensions().x;
		destRect.w = b.getDimensions().y;
		m_debugRenderer.drawBox(destRect, Engine::ColorRGBA8(255, 255, 255, 255), b.getBody()->GetAngle());
	}

	m_player.drawDebug(m_debugRenderer);

	m_debugRenderer.end();
	m_debugRenderer.render(projectionMatrix, 2.0f);

	m_textureProgram.use();
	m_debugTextSpriteBatch.begin();

	char buffer[256];

	sprintf_s(buffer, "%.2f fps", m_game->getFps());
	m_spriteFont->draw(m_debugTextSpriteBatch, buffer, glm::vec2((m_window->getScreenWidth() / -2.0f) / m_camera.getScale(), (m_window->getScreenHeight() / 2.0f) / m_camera.getScale() - 1.0f), glm::vec2(0.01f), 0.0f, Engine::ColorRGBA8(255, 255, 255, 255));
	
	sprintf_s(buffer, "onGround: %s", m_player.isOnGround() ? "true" : "false");
	m_spriteFont->draw(m_debugTextSpriteBatch, buffer, glm::vec2((m_window->getScreenWidth() / -2.0f) / m_camera.getScale(), (m_window->getScreenHeight() / 2.0f) / m_camera.getScale() - 1.5f), glm::vec2(0.01f), 0.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	sprintf_s(buffer, "(%f, %f)", m_player.getCapsule().getBody()->GetPosition().x, m_player.getCapsule().getBody()->GetPosition().y);
	m_spriteFont->draw(m_debugTextSpriteBatch, buffer, glm::vec2((m_window->getScreenWidth() / -2.0f) / m_camera.getScale(), (m_window->getScreenHeight() / 2.0f) / m_camera.getScale() - 2.0f), glm::vec2(0.01f), 0.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	m_debugTextSpriteBatch.end();
	m_debugTextSpriteBatch.renderBatch();
	m_textureProgram.unuse();
}

bool GameplayScreen::onExitClicked(const CEGUI::EventArgs& e)
{
	m_currentState = Engine::ScreenState::EXIT_APPLICATION;

	return true;
}
