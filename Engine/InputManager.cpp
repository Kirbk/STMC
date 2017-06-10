#include "InputManager.h"


namespace Engine{

	int MAX_CONTROLLERS = 4;

	InputManager::InputManager() : _mouseCoords(0.0f)
	{
		SDL_JoystickEventState(SDL_ENABLE);

		for (int i = 0; i < MAX_CONTROLLERS; i++) {
			m_controllers.push_back(nullptr);
		}
	}


	InputManager::~InputManager()
	{
		for (int i = 0; i < m_controllers.size(); i++) {
			delete m_controllers[i];
		}

		m_controllers.resize(0);
	}

	void InputManager::update() {

		for (auto& it : _keyMap) {
			_previousKeyMap[it.first] = it.second;
		}
	}

	void InputManager::keyPressed(unsigned int keyID) {
		_keyMap[keyID] = true;
	}


	void InputManager::keyReleased(unsigned int keyID) {
		_keyMap[keyID] = false;
	}

	void InputManager::setScrolling(bool scroll, float amount)
	{
		m_isScrolling = scroll;
		m_scrollAmount = amount;
	}

	void InputManager::setMouseCoords(float x, float y) {
		_mouseCoords.x = x;
		_mouseCoords.y = y;
	}

	bool InputManager::isKeyDown(unsigned int keyID) {
		auto it = _keyMap.find(keyID);
		if (it != _keyMap.end())
			return it->second;
		else
			return false;
	}

	bool InputManager::isKeyPressed(unsigned int keyID) {
		if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false) {
			return true;
		}

		return false;
	}

	void InputManager::buttonPressed(unsigned int buttonID)
	{
		m_buttonMap[buttonID] = true;
	}

	void InputManager::buttonReleased(unsigned int buttonID)
	{
		m_buttonMap[buttonID] = false;
	}

	bool InputManager::isButtonDown(unsigned int buttonID, unsigned int controllerIndex)
	{
		auto it = m_buttonMap.find(buttonID);
	}

	Controller* InputManager::addController()
	{
		for (int i = 0; i < MAX_CONTROLLERS; i++) {
			if (m_controllers[i] == nullptr) {
				Controller* c = new Controller();
				c->index = i;
				c->joystick = SDL_JoystickOpen(i);
				m_controllers[i] = c;
				return m_controllers[i];
				delete c;
				break;
			}
		}

		return nullptr;
	}

	void InputManager::removeContoller(int index)
	{
		SDL_JoystickClose(m_controllers[index]->joystick);
		delete m_controllers[index];
		m_controllers[index] = nullptr;
		std::printf("%i", index);
	}

	bool InputManager::wasKeyDown(unsigned int keyID) {
		auto it = _previousKeyMap.find(keyID);
		if (it != _previousKeyMap.end())
			return it->second;
		else
			return false;
	}
}