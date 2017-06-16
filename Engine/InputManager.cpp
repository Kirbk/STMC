#include "InputManager.h"

#include <iostream>
#include <bitset>

namespace Engine{
	InputManager::InputManager() : _mouseCoords(0.0f)
	{
		SDL_JoystickEventState(SDL_ENABLE);

		for (int i = 0; i < MAX_CONTROLLERS; i++) {
			m_controllers[i] = nullptr;
		}
	}


	InputManager::~InputManager()
	{
		for (int i = 0; i < sizeof(m_controllers) / sizeof(Controller*); i++) {
			if (m_controllers[i] != nullptr) {
				for (int j = 0; j < m_controllers[i]->axes.size(); j++) {
					if (m_controllers[i]->axes[j] != nullptr) {
						delete m_controllers[i]->axes[j];
					}
				}

				m_controllers[i]->axes.resize(0);
				delete m_controllers[i];
			}
		}
	}

	void InputManager::update() {

		for (auto& it : _keyMap) {
			_previousKeyMap[it.first] = it.second;
		}

		for (int i = 0; i < MAX_CONTROLLERS; i++) {
			if (m_controllers[i] != nullptr) {
				if (!SDL_JoystickGetAttached(m_controllers[i]->joystick)) {
					for (int j = 0; j < m_controllers[i]->axes.size(); j++) {
						delete m_controllers[i]->axes[j];
					}
					m_controllers[i]->isBinded = false;

					m_controllers[i]->axes.resize(0);

					SDL_JoystickClose(m_controllers[i]->joystick);
					delete m_controllers[i];
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
		m_controllers[m_totalControllers - controllerIndex - 1]->buttonMap[buttonID] = true;
	}

	void InputManager::buttonReleased(unsigned int buttonID, unsigned int controllerIndex)
	{
		m_controllers[m_totalControllers - controllerIndex - 1]->buttonMap[buttonID] = false;
	}

	bool InputManager::isButtonDown(unsigned int buttonID, unsigned int controllerIndex)
	{
		auto it = m_controllers[m_totalControllers - controllerIndex - 1]->buttonMap.find(buttonID);
		if (it != m_controllers[m_totalControllers - controllerIndex - 1]->buttonMap.end())
			return it->second;
		else
			return false;
	}

	void InputManager::addController()
	{
		for (int i = 0; i < MAX_CONTROLLERS; i++) {
			int cIndex = m_totalControllers - i;
			if (m_controllers[i] == nullptr) {
				m_controllers[i] = new Controller();
				m_controllers[i]->index = i;
				m_controllers[i]->SDL_Index = m_totalControllers;
				m_controllers[i]->joystick = SDL_JoystickOpen(i);

				//std::cout << i << std::endl;

				m_controllers[i]->axes.resize(6, nullptr);

				m_totalControllers++;

				break;
			}
		}
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
		int cIndex = m_totalControllers;

		


		for (Controller* c : m_controllers) {
			if (c != nullptr) {
				if (c->SDL_Index == controllerIndex) {
					std::cout << c->SDL_Index << " | " << controllerIndex << " | " << c->index << std::endl;

					if (c->axes[axis] != nullptr) {
						c->axes[axis]->axisValue = (int)value;
					}
					else {
						c->axes[axis] = new Axis();
						c->axes[axis]->axisID = axis;
						c->axes[axis]->axisValue = value;
						c->axes[axis]->deadZone = m_controllerDeadZone;
					}
				}
			}
		}


		/*if (m_controllers[cIndex] != nullptr) {
			//std::cout << axis << std::endl;
			if (m_controllers[cIndex]->axes[axis] != nullptr) {
				m_controllers[cIndex]->axes[axis]->axisValue = (int)value;


				//std::printf("%i\n", controllerIndex);
			}
			else {
				m_controllers[cIndex]->axes[axis] = new Axis();
				m_controllers[cIndex]->axes[axis]->axisID = axis;
				m_controllers[cIndex]->axes[axis]->axisValue = value;
				m_controllers[cIndex]->axes[axis]->deadZone = m_controllerDeadZone;
			}
		}*/
	}

	void InputManager::setHat(char hat, int controllerIndex)
	{
		m_controllers[m_totalControllers - controllerIndex - 1]->hat = hat;
	}

	bool InputManager::isHatDown(char hat, int controllerIndex)
	{
		if ((hat & m_controllers[m_totalControllers - controllerIndex - 1]->hat) == hat) {
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