#pragma once

#include <unordered_map>
#include <glm.hpp>
#include <SDL.h>

namespace Engine{

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

		glm::vec2 getMouseCoords() const {
			return _mouseCoords;
		}

		float getScrollAmount() const { return m_scrollAmount; }

	private:
		bool wasKeyDown(unsigned int keyID);
		bool m_isScrolling = false;

		std::unordered_map<unsigned int, bool> _keyMap;
		std::unordered_map<unsigned int, bool> _previousKeyMap;

		glm::vec2 _mouseCoords;
		float m_scrollAmount = 0;
	};

}