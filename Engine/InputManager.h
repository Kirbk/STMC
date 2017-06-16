#pragma once

#include <unordered_map>
#include <glm.hpp>
#include <SDL.h>

namespace Engine{
	enum class XBOX360Axes {
		leftStickX = 0,
		leftStickY = 1,
		leftTrigger = 2,
		rightStickX = 3,
		rightStickY = 4,
		rightTrigger = 5
	};

	enum class XBOX360Buttons
	{
		A = 0,
		B = 1,
		X = 2,
		Y = 3,
		LEFT_BUMPER = 4,
		RIGHT_BUMPER = 5,
		BACK = 6,
		START = 7,
		LEFT_STICK = 8,
		RIGHT_STICK = 9
	};

	enum class XBOX360Hat {
		MIDDLE = 0b00000000,
		UP = 0b00000001,
		RIGHT = 0b00000010,
		DOWN = 0b00000100,
		LEFT = 0b00001000
	};

	struct Axis {
		unsigned int axisID;
		int axisValue;
		float deadZone;
	};

	struct Controller {
		SDL_Joystick* joystick;
		int index = 0;
		int SDL_Index = 0;
		std::unordered_map<unsigned int, bool> buttonMap;
		std::unordered_map<unsigned int, bool> previousButtonMap;
		std::vector<Axis*> axes; // Stupid but too far to turn back
		char hat = 0;
		bool isBinded = false;
	};

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void update();

		void keyPressed(unsigned int keyID);
		void keyReleased(unsigned int keyID);
		void setScrolling(bool scroll, float amount = 0);

		void setMouseCoords(float x, float y);

		bool isKeyDown(unsigned int keyID);
		bool isKeyPressed(unsigned int keyID);
		bool isScrolling() { return m_isScrolling; }

		void buttonPressed(unsigned int buttonID, unsigned int controllerIndex);
		void buttonReleased(unsigned int buttonID, unsigned int controllerIndex);

		bool isButtonDown(unsigned int buttonID, unsigned int controllerIndex);

		glm::vec2 getMouseCoords() const {
			return _mouseCoords;
		}

		float getScrollAmount() const { return m_scrollAmount; }
		void addController();
		void removeContoller(int index);

		Controller* getController(int index) { 
			if (sizeof(m_controllers) / sizeof(Controller*) <= MAX_CONTROLLERS) {
				return m_controllers[index];
			}
			else {
				return nullptr;
			}
		}

		void setAxisValue(unsigned int controllerIndex, unsigned int axis, int value);

		void setControllerDeadZone(float value) { m_controllerDeadZone = value; }
		const float getControllerDeadZone() const { return m_controllerDeadZone; }

		void setHat(char hat, int controllerIndex);
		bool isHatDown(char hat, int controllerIndex);

		const int getMaxControllers() const { return MAX_CONTROLLERS; }

	private:
		bool wasKeyDown(unsigned int keyID);
		bool m_isScrolling = false;

		std::unordered_map<unsigned int, bool> _keyMap;
		std::unordered_map<unsigned int, bool> _previousKeyMap;

		glm::vec2 _mouseCoords;
		float m_scrollAmount = 0;
		int MAX_CONTROLLERS = 4;
		Controller* m_controllers[4];
		float m_controllerDeadZone = 0;
		int m_totalControllers = 0;
	};

}