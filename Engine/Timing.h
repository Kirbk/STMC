#pragma once

namespace Engine {
	class FpsLimiter {
	public:
		FpsLimiter();

		void setMaxFPS(float maxFPS);
		
		void init(float maxFPS);

		void begin();
		float end();
	private:
		void calculateFPS();

		float _fps;
		float _maxFps;
		float _frameTime;

		unsigned int _startTicks;
	};
}