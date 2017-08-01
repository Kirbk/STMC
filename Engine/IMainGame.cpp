#include "IMainGame.h"
#include "Timing.h"
#include "ScreenList.h"
#include "IGameScreen.h"
#include <iostream>
#include <bitset>
#include "Command.h"
#include <Windows.h>
#include <algorithm>
#include <sstream>

namespace Engine {

	IMainGame::IMainGame() {
		m_screenList = std::make_unique<ScreenList>(this);
	}

	IMainGame::~IMainGame() {

	}

	std::string make_lowercase(const std::string& in)
	{
		std::string out;

		std::transform(in.begin(), in.end(), std::back_inserter(out), ::tolower);
		return out;
	}

	void IMainGame::run() {
		//Command com([this]() { std::cout << m_windowName << "\n"; });
		//addCommand("testCommand", com);

		//com.execute();

		gameThread = std::thread(&IMainGame::m_run, this);

		Sleep(5000);
		while (m_isRunning) {
			updateConsole();
		}

		gameThread.join();
	}

	void IMainGame::exitGame() {
		m_currentScreen->onExit();
		if (m_screenList) {
			m_screenList->destroy();
			m_screenList.reset();
		}

		m_isRunning = false;

		exit(0);
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
			inputManager.setScrolling(true, (float)evnt.wheel.y);
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
			//inputManager.keyReleased(evnt.button.button);
			break;
		case SDL_JOYBUTTONDOWN:
			//inputManager.buttonPressed(evnt.jbutton.button, evnt.jbutton.which);
			break;
		case SDL_JOYBUTTONUP:
			//inputManager.buttonReleased(evnt.jbutton.button, evnt.jbutton.which);
			break;
		case SDL_JOYDEVICEADDED:
			//inputManager.addController();
			break;
		case SDL_JOYDEVICEREMOVED:
			//inputManager.removeContoller(evnt.jdevice.which);
			break;
		case SDL_JOYAXISMOTION:
			//std::cout << evnt.jaxis.which << std::endl;
			//inputManager.setAxisValue(evnt.jaxis.which, evnt.jaxis.axis, evnt.jaxis.value);
			break;
		case SDL_JOYHATMOTION:
		{
			//inputManager.setHat(evnt.jhat.value, evnt.jhat.which);
			break;
		}
		default:
			inputManager.setScrolling(false);
			break;
		}
	}

	bool IMainGame::initSystems() {
		m_window.create(m_windowName, m_width, m_height, m_windowFlags);

		return true;
	}

	void IMainGame::addCommand(std::string label, Command* command)
	{
		auto mit = m_commandMap.find(make_lowercase(label));

		if (mit == m_commandMap.end()) {
			//Insert it into the map
			m_commandMap.insert(make_pair(make_lowercase(label), command));
		}
	}

	void IMainGame::updateConsole()
	{
		if (&m_windowName) {
			std::string label = "";
			std::cout << "[" << m_windowName << "] ";
			std::getline(std::cin, label);

			std::istringstream iss(label);
			std::vector<std::string> tokens;

			for (std::string each; std::getline(iss, each, ' '); tokens.push_back(each));

			auto mit = m_commandMap.find(make_lowercase(tokens[0]));

			tokens.erase(tokens.begin());

			if (mit != m_commandMap.end()) {
				mit->second->execute(tokens);
			}
			else {
				printf("\nUnknown command! %s could not be found.\nPlease consider getting better at life.\n\n", label.c_str());
			}
		}
	}

	bool IMainGame::is_digits(const std::string & str)
	{
		if (str == std::string("-")) return false;
		return str.find_first_not_of("0123456789-") == std::string::npos;
	}

	void IMainGame::m_run(IMainGame* currentGame)
	{
		if (!currentGame->init()) return;

		currentGame->m_isRunning = true;

		FpsLimiter limiter;
		limiter.init(60.0f);

		while (currentGame->m_isRunning) {
			limiter.begin();

			currentGame->inputManager.update();

			currentGame->update();
			if (currentGame->m_isRunning) {
				currentGame->draw();

				currentGame->m_fps = limiter.end();
				currentGame->m_window.swapBuffer();
			}
		}
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