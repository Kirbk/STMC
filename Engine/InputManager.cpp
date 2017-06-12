#include "InputManager.h"

#include <iostream>
#include <bitset>

namespace Engine{
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
			for (int j = 0; j < m_controllers[i]->axes.size(); i++) {
				delete m_controllers[i]->axes[j];
			}

			m_controllers[i]->axes.resize(0);
			delete m_controllers[i];
		}

		m_controllers.resize(0);
	}

	void InputManager::update() {

		for (auto& it : _keyMap) {
			_previousKeyMap[it.first] = it.second;
		}

		for (int i = 0; i < MAX_CONTROLLERS; i++) {
			if (m_controllers[i] != nullptr) {
				if (!SDL_JoystickGetAttached(m_controllers[i]->joystick)) {
					SDL_JoystickClose(m_controllers[i]->joystick);
					m_controllers[i] = nullptr;
				}
			}
			if (m_controllers[i] != nullptr) {
				for (auto& it : m_controllers[i]->buttonMap) {
					m_controllers[i]->previousButtonMap[it.first] = it.second;
				}
			}
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

	void InputManager::buttonPressed(unsigned int buttonID, unsigned int controllerIndex)
	{
		m_controllers[controllerIndex]->buttonMap[buttonID] = true;
	}

	void InputManager::buttonReleased(unsigned int buttonID, unsigned int controllerIndex)
	{
		m_controllers[controllerIndex]->buttonMap[buttonID] = false;
	}

	bool InputManager::isButtonDown(unsigned int buttonID, unsigned int controllerIndex)
	{
		auto it = m_controllers[controllerIndex]->buttonMap.find(buttonID);
		if (it != m_controllers[controllerIndex]->buttonMap.end())
			return it->second;
		else
			return false;
	}

	Controller* InputManager::addController()
	{
		for (int i = 0; i < MAX_CONTROLLERS; i++) {
			if (m_controllers[i] == nullptr) {
				Controller* c = new Controller();
				c->index = i;
				c->joystick = SDL_JoystickOpen(i);
				c->axes.resize(6, nullptr);
				m_controllers[i] = c;

				return m_controllers[i];
				delete c;
				break;
			}
		}

		return nullptr;
	}

	// Deprecated
	void InputManager::removeContoller(int index)
	{
		if (m_controllers[index] != nullptr) {
			if (SDL_JoystickGetAttached(m_controllers[index]->joystick)) {
				SDL_JoystickClose(m_controllers[index]->joystick);
				delete m_controllers[index];
				m_controllers[index] = nullptr;
			}
		}
	}

	

	void InputManager::setAxisValue(unsigned int controllerIndex, unsigned int axis, int value)
	{
		if (m_controllers[controllerIndex]->axes[axis] != nullptr) {
			m_controllers[controllerIndex]->axes[axis]->axisValue = (int)value;

			//std::printf("%i\n", (int) value);
		}
		else {
			Axis* tempAxis = new Axis();
			tempAxis->axisID = axis;
			tempAxis->axisValue = value;
			tempAxis->deadZone = m_controllerDeadZone;
			m_controllers[controllerIndex]->axes[axis] = tempAxis;
		}
	}

	void InputManager::setHat(char hat, int controllerIndex)
	{
		m_controllers[controllerIndex]->hat = hat;
	}

	bool InputManager::isHatDown(char hat, int controllerIndex)
	{
		if ((hat & m_controllers[controllerIndex]->hat) == hat) {
			return true;
		}
		else {
			return false;
		}
	}

	bool InputManager::wasKeyDown(unsigned int keyID) {
		auto it = _previousKeyMap.find(keyID);
		if (it != _previousKeyMap.end())
			return it->second;
		else
			return false;
	}
}