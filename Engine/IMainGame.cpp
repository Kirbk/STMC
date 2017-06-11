#include "IMainGame.h"
#include "Timing.h"
#include "ScreenList.h"
#include "IGameScreen.h"
#include <iostream>

namespace Engine{

	IMainGame::IMainGame() {
		m_screenList = std::make_unique<ScreenList>(this);
	}

	IMainGame::~IMainGame() {

	}

	void IMainGame::run() {
		if (!init()) return;

		m_isRunning = true;
		
		FpsLimiter limiter;
		limiter.init(60.0f);

		while (m_isRunning) {
			limiter.begin();

			inputManager.update();

			update();
			if (m_isRunning) {
				draw();

				m_fps = limiter.end();
				m_window.swapBuffer();
			}
		}
	}

	void IMainGame::exitGame() {
		m_currentScreen->onExit();
		if (m_screenList) {
			m_screenList->destroy();
			m_screenList.reset();
		}

		m_isRunning = false;
	}

	bool IMainGame::init() {

		Engine::init();

		if (!initSystems()) return false;

		onInit();
		addScreens();

		m_currentScreen = m_screenList->getCurrent();
		m_currentScreen->onEntry();
		m_currentScreen->setRunning();

		return true;
	}

	void IMainGame::onSDLEvent(SDL_Event& evnt) {
		switch (evnt.type) {
		case SDL_QUIT:
			exitGame();
			break;
		case SDL_MOUSEMOTION:
			inputManager.setMouseCoords((float)evnt.motion.x, (float)evnt.motion.y);
			break;
		case SDL_MOUSEWHEEL:
			inputManager.setScrolling(true, (float) evnt.wheel.y);
			break;
		case SDL_KEYDOWN:
			inputManager.keyPressed(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			inputManager.keyReleased(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			inputManager.keyPressed(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			inputManager.keyReleased(evnt.button.button);
			break;
		case SDL_JOYDEVICEADDED:
			inputManager.addController();
			break;
		case SDL_JOYDEVICEREMOVED:
			//inputManager.removeContoller(evnt.jdevice.which);
			break;
		default:
			inputManager.setScrolling(false);
			break;
		}
	}

	bool IMainGame::initSystems() {
		m_window.create(m_windowName, m_width, m_height, m_windowFlags);

		return true;
	}


	void IMainGame::update() {
		if (m_currentScreen) {
			switch (m_currentScreen->getState()) {
			case ScreenState::RUNNING:
				m_currentScreen->update();
				break;
			case ScreenState::CHANGE_NEXT:
				m_currentScreen->onExit();
				m_currentScreen = m_screenList->moveNext();
				if (m_currentScreen) {
					m_currentScreen->setRunning();
					m_currentScreen->onEntry();
				}
				break;
			case ScreenState::CHANGE_PREVIOUS:
				m_currentScreen->onExit();
				m_currentScreen = m_screenList->movePrevious();
				if (m_currentScreen) {
					m_currentScreen->setRunning();
					m_currentScreen->onEntry();
				}
				break;
			case ScreenState::EXIT_APPLICATION:
				exitGame();
				break;
			default:
				break;
			}
		}
		else {
			exitGame();
		}
	}

	void IMainGame::draw() {
		if (m_currentScreen && m_currentScreen->getState() == ScreenState::RUNNING) {
			m_currentScreen->draw();
		}
	}

}