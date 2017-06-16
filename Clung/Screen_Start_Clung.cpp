#include "Screen_Start_Clung.h"

#include <Engine\IMainGame.h>

Screen_Start_Clung::Screen_Start_Clung(Engine::Window* window) : m_window(window)
{
	m_screenIndex = SCREEN_INDEX_MAINMENU;
}


Screen_Start_Clung::~Screen_Start_Clung()
{
}

int Screen_Start_Clung::getNextScreenIndex() const
{
	return m_nextScreenIndex;
}

int Screen_Start_Clung::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_MAINMENU;
}

void Screen_Start_Clung::build()
{
}

void Screen_Start_Clung::destroy()
{
}

void Screen_Start_Clung::onEntry()
{
	m_textSpriteBatch.init();
	m_spriteFont = new Engine::SpriteFont("Assets/fonts/Oswald-SemiBold.ttf", 128);

	// Init camera
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setScale(25.0f);

	m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/fragmentShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();

	initUI();
}

void Screen_Start_Clung::onExit()
{
	m_gui.destroy();
}

void Screen_Start_Clung::update()
{
	m_camera.update();
	checkInput();
}

void Screen_Start_Clung::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

	m_gui.draw();

	m_textureProgram.use();

	glm::mat4 textProjectionMatrix = m_camera.getCameraMatrix();
	GLint textpUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(textpUniform, 1, GL_FALSE, &textProjectionMatrix[0][0]);

	m_textSpriteBatch.begin();

	char buffer[256];
	sprintf_s(buffer, "CLUNG");
	m_spriteFont->draw(m_textSpriteBatch, buffer, glm::vec2(0, 2.5f), glm::vec2(0.05), 0.0f, Engine::ColorRGBA8(255, 255, 255, 255), Engine::Justification::MIDDLE);

	m_textSpriteBatch.end();
	m_textSpriteBatch.renderBatch();
	m_textureProgram.unuse();
}

void Screen_Start_Clung::initUI()
{
	m_gui.init("GUI");
	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.loadScheme("AlfiskoSkin.scheme");
	m_gui.setFont("DejaVuSans-10");

	CEGUI::PushButton* startGameButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("AlfiskoSkin/Button", glm::vec4(0.45f, 0.5f, 0.1f, 0.05f), glm::vec4(0), "StartGame"));
	startGameButton->setText("Start Game");
	startGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Screen_Start_Clung::onNewGameClicked, this));

	CEGUI::PushButton* editorButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("AlfiskoSkin/Button", glm::vec4(0.45f, 0.55f, 0.1f, 0.05f), glm::vec4(0), "Editor"));
	editorButton->setText("Level Editor");
	editorButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Screen_Start_Clung::onEditorClicked, this));

	CEGUI::PushButton* exitGameButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("AlfiskoSkin/Button", glm::vec4(0.45f, 0.6f, 0.1f, 0.05f), glm::vec4(0), "ExitGame"));
	exitGameButton->setText("Exit Game");
	exitGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Screen_Start_Clung::onExitClicked, this));
}

void Screen_Start_Clung::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);
		m_gui.onSDLEvent(evnt);

		if (evnt.type == SDL_QUIT) {
			m_currentState = Engine::ScreenState::EXIT_APPLICATION;
		}
	}
}

bool Screen_Start_Clung::onNewGameClicked(const CEGUI::EventArgs & e)
{
	m_nextScreenIndex = SCREEN_INDEX_GAMEPLAY;
	m_currentState = Engine::ScreenState::CHANGE_NEXT;
	return true;
}

bool Screen_Start_Clung::onEditorClicked(const CEGUI::EventArgs & e)
{
	
	return true;
}

bool Screen_Start_Clung::onExitClicked(const CEGUI::EventArgs & e)
{
	m_currentState = Engine::ScreenState::EXIT_APPLICATION;
	return true;
}
