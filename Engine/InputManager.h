#pragma once

#include <unordered_map>
#include <glm.hpp>
#include <SDL.h>

namespace Engine{

	struct Controller {
		SDL_Joystick* joystick;
		int index = 0;
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

		void buttonPressed(unsigned int buttonID);
		void buttonReleased(unsigned int buttonID);

		bool isButtonDown(unsigned int buttonID, unsigned int controllerIndex);

		glm::vec2 getMouseCoords() const {
			return _mouseCoords;
		}

		float getScrollAmount() const { return m_scrollAmount; }
		Controller* addController();
		void removeContoller(int index);

		std::vector<Controller*> controllers;

	private:
		bool wasKeyDown(unsigned int keyID);
		bool m_isScrolling = false;

		std::unordered_map<unsigned int, bool> _keyMap;
		std::unordered_map<unsigned int, bool> _previousKeyMap;

		std::unordered_map<unsigned int, bool> m_buttonMap;
		std::unordered_map<unsigned int, bool> m_previousButtonMap;

		glm::vec2 _mouseCoords;
		float m_scrollAmount = 0;
		std::vector<Controller*> m_controllers;
	};

}