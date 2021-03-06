#include "Screen_GP_Clung.h"

#include <Engine\IMainGame.h>
#include <iostream>

#include "Wall_Clung.h"


Screen_GP_Clung::Screen_GP_Clung(Engine::Window* window) : m_window(window)
{
	m_screenIndex = SCREEN_INDEX_GAMEPLAY;
}


Screen_GP_Clung::~Screen_GP_Clung()
{
}

int Screen_GP_Clung::getNextScreenIndex() const {
	return SCREEN_INDEX_NO_SCREEN;
}

int Screen_GP_Clung::getPreviousScreenIndex() const {
	return SCREEN_INDEX_MAINMENU;
}

void Screen_GP_Clung::build()
{
}

void Screen_GP_Clung::destroy()
{
}

void Screen_GP_Clung::onEntry()
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
	// Compile our light shader
	m_lightProgram.compileShaders("Shaders/lightShading.vert", "Shaders/lightShading.frag");
	m_lightProgram.addAttribute("vertexPosition");
	m_lightProgram.addAttribute("vertexColor");
	m_lightProgram.addAttribute("vertexUV");
	m_lightProgram.linkShaders();

	// Init camera
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setScale(25.0f);

	m_displayCamera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_displayCamera.setPosition(glm::vec2(m_window->getScreenWidth() / 2, m_window->getScreenHeight() / 2));
	//m_displayCamera.setScale(25.0f);

	// Init player
	m_entities.push_back(new Player_Clung(100));
	m_entities.back()->init(m_world.get(), glm::vec2(0.0f), glm::vec2(1.0f, 0.0f), 150.0f, glm::vec2(2.0f), glm::vec2(2.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), &m_camera, Engine::ColorRGBA8(255, 255, 255, 255), &m_game->inputManager);
	m_player = static_cast<Player_Clung*>(m_entities.back());
	m_allEntities.push_back(m_entities.back());

	m_items.push_back(new MedKit_Clung(20));
	m_items.back()->init(m_world.get(), glm::vec2(6.0f, 5.0f), glm::vec2(1.0f, 0.0f), 0.0f, glm::vec2(1.0f), glm::vec2(1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), &m_camera, Engine::ColorRGBA8(255, 255, 255, 255));
	m_allEntities.push_back(m_items.back());
}

void Screen_GP_Clung::onExit()
{
	delete m_player;
	m_player = nullptr;

	m_world.reset();
	m_entities.clear();
	m_items.clear();
	m_lights.clear();

	m_debugRenderer.dispose();
}

void Screen_GP_Clung::update()
{
	m_camera.setPosition(glm::vec2(m_player->getCircle().getBody()->GetPosition().x, m_player->getCircle().getBody()->GetPosition().y));
	m_camera.update();
	m_displayCamera.update();
	checkInput();

	for (int i = 0; i < m_entities.size(); i++) {
		if (m_entities[i] != nullptr) {
			m_entities[i]->update();
		}
	}
	
	for (Item_Clung* e : m_items) {
		if (e != nullptr) {
			if (e->isDestroyed()) {
				m_items.erase(std::remove(m_items.begin(), m_items.end(), e), m_items.end());
				delete e;
			}
			else {
				e->update();
			}
		}
	}

	for (Light_Clung* l : m_lights) {
		l->update(m_allEntities);
	}

	// Update physics
	if (m_world.get() != nullptr)
		m_world->Step(1.0f / 60.0f, 32, 16);
}

void Screen_GP_Clung::draw()
{
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
	
	for (Entity_Clung* e : m_entities) {
		if (m_camera.isBoxInView(e->getPosition() - (e->getDrawDims() / 2.0f), e->getDrawDims())) {
			e->draw(m_spriteBatch);
		}
	}

	for (Item_Clung* e : m_items) {
		if (m_camera.isBoxInView(e->getPosition() - (e->getDrawDims() / 2.0f), e->getDrawDims())) {
			e->draw(m_spriteBatch);
		}
	}

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_textureProgram.unuse();

	renderGUI(projectionMatrix);

	if (m_debug) renderDebug(projectionMatrix);
}

void Screen_GP_Clung::checkInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);
	}

	

	if (m_game->inputManager.isKeyPressed(SDLK_F8)) {
		m_debug = !m_debug;
	}
}

void Screen_GP_Clung::renderGUI(glm::mat4 & projectionMatrix)
{
	m_textureProgram.use();

	glm::mat4 textProjectionMatrix = m_displayCamera.getCameraMatrix();
	GLint textpUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(textpUniform, 1, GL_FALSE, &textProjectionMatrix[0][0]);

	m_textSpriteBatch.begin();

	char buffer[256];
	sprintf_s(buffer, "Health: %.f", m_player->getHealth());
	m_spriteFont->draw(m_textSpriteBatch, buffer, glm::vec2(0.0f, 0.0f), glm::vec2(0.25), 0.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	if (m_debug) renderDebugText(projectionMatrix);
	m_textSpriteBatch.end();
	m_textSpriteBatch.renderBatch();
	m_textureProgram.unuse();
}


void Screen_GP_Clung::renderDebug(glm::mat4& projectionMatrix) {
	//DRAW HITBOXES
	m_player->drawDebug(m_debugRenderer);
	
	for (Entity_Clung* e : m_entities) {
		if (e->getType() == EntityCategory::BOUNDARY) {
			static_cast<Wall_Clung*>(e)->drawDebug(m_debugRenderer);
		}
	}

	for (Item_Clung* e : m_items) {
		if (e->getItemType() == ItemList::MedKit) {
			static_cast<MedKit_Clung*>(e)->drawDebug(m_debugRenderer);
		}
	}

	for (Light_Clung* l : m_lights) {
		l->drawDebug(m_debugRenderer);
	}

	m_debugRenderer.end();
	m_debugRenderer.render(projectionMatrix, 2.0f);
}

void Screen_GP_Clung::renderDebugText(glm::mat4 & projectionMatrix)
{
	char buffer[256];

	sprintf_s(buffer, "(%.3f, %.3f) : %.2f fps", m_player->getCircle().getBody()->GetPosition().x, m_player->getCircle().getBody()->GetPosition().y, m_game->getFps());
	m_spriteFont->draw(m_textSpriteBatch, buffer, glm::vec2(0.0f, m_window->getScreenHeight() - m_spriteFont->getFontHeight() / 4), glm::vec2(0.25), 0.0f, Engine::ColorRGBA8(255, 255, 255, 255));
}
