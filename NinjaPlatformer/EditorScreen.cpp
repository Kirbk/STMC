#include "EditorScreen.h"



EditorScreen::EditorScreen(Engine::Window* window) : m_window(window)
{
	m_screenIndex = SCREEN_INDEX_EDITOR;
}


EditorScreen::~EditorScreen()
{
}

int EditorScreen::getNextScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

int EditorScreen::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_MAINMENU;
}

void EditorScreen::build()
{
}

void EditorScreen::destroy()
{
}

void EditorScreen::onEntry()
{
	// Init camera
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setScale(25.0f);

	initUI();
}

void EditorScreen::onExit()
{
	m_gui.destroy();
}

void EditorScreen::update()
{
	m_camera.update();
	checkInput();
}

void EditorScreen::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

	m_gui.draw();
}

void EditorScreen::initUI()
{
	m_gui.init("GUI");
	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.loadScheme("AlfiskoSkin.scheme");
	m_gui.setFont("DejaVuSans-10");

	CEGUI::Slider* rSlider = static_cast<CEGUI::Slider*>(m_gui.createWidget("TaharezLook/Slider", glm::vec4(0.05f, 0.05f, 0.02f, 0.2f), glm::vec4(0.0f), "RedSlider"));
	rSlider->setMaxValue(255.0f);
	rSlider->setCurrentValue(m_colorPickerRed);

	m_gui.setMouseCursor("AlfiskoSkin/MouseArrow");
	m_gui.showMouseCursor();
	SDL_ShowCursor(SDL_FALSE);
}

void EditorScreen::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_gui.onSDLEvent(evnt);

		if (evnt.type == SDL_QUIT) {
			m_currentState = Engine::ScreenState::EXIT_APPLICATION;
		}
	}
}

bool EditorScreen::onExitClicked(const CEGUI::EventArgs & e)
{
	m_currentState = Engine::ScreenState::EXIT_APPLICATION;
	return true;
}
