#include "MainMenuScreen.h"

MainMenuScreen::MainMenuScreen(Engine::Window* window) : m_window(window)
{
	m_screenIndex = SCREEN_INDEX_MAINMENU;
}


MainMenuScreen::~MainMenuScreen()
{
}

int MainMenuScreen::getNextScreenIndex() const
{
	return m_nextScreenIndex;
}

int MainMenuScreen::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

void MainMenuScreen::build()
{
}

void MainMenuScreen::destroy()
{
}

void MainMenuScreen::onEntry()
{
	// Init camera
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setScale(25.0f);

	initUI();
}

void MainMenuScreen::onExit()
{
	m_gui.destroy();
}

void MainMenuScreen::update()
{
	m_camera.update();
	checkInput();
}

void MainMenuScreen::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

	m_gui.draw();
}

void MainMenuScreen::initUI()
{
	m_gui.init("GUI");
	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.loadScheme("AlfiskoSkin.scheme");
	m_gui.setFont("DejaVuSans-10");

	CEGUI::PushButton* startGameButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("AlfiskoSkin/Button", glm::vec4(0.45f, 0.5f, 0.1f, 0.05f), glm::vec4(0), "StartGame"));
	startGameButton->setText("Start Game");
	startGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenuScreen::onNewGameClicked, this));

	CEGUI::PushButton* editorButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("AlfiskoSkin/Button", glm::vec4(0.45f, 0.55f, 0.1f, 0.05f), glm::vec4(0), "Editor"));
	editorButton->setText("Level Editor");
	editorButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenuScreen::onEditorClicked, this));

	CEGUI::PushButton* exitGameButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("AlfiskoSkin/Button", glm::vec4(0.45f, 0.6f, 0.1f, 0.05f), glm::vec4(0), "ExitGame"));
	exitGameButton->setText("Exit Game");
	exitGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenuScreen::onExitClicked, this));


	m_gui.setMouseCursor("AlfiskoSkin/MouseArrow");
	m_gui.showMouseCursor();
	SDL_ShowCursor(false);
}

void MainMenuScreen::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_gui.onSDLEvent(evnt);

		if (evnt.type == SDL_QUIT) {
			m_currentState = Engine::ScreenState::EXIT_APPLICATION;
		}
	}
}

bool MainMenuScreen::onNewGameClicked(const CEGUI::EventArgs & e)
{
	m_nextScreenIndex = SCREEN_INDEX_GAMEPLAY;
	m_currentState = Engine::ScreenState::CHANGE_NEXT;
	return true;
}

bool MainMenuScreen::onEditorClicked(const CEGUI::EventArgs & e)
{
	m_nextScreenIndex = SCREEN_INDEX_EDITOR;
	m_currentState = Engine::ScreenState::CHANGE_NEXT;
	return true;
}

bool MainMenuScreen::onExitClicked(const CEGUI::EventArgs & e)
{
	m_currentState = Engine::ScreenState::EXIT_APPLICATION;
	return true;
}
