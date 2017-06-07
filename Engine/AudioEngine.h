#pragma once

#include <SDL_mixer.h>
#include <string>
#include <map>
#include <vector>

namespace Engine{

	class SoundEffect {
	public:
		friend class AudioEngine;
		SoundEffect();

		void play(int loops = 0);

	private:
		Mix_Chunk* m_chunk = nullptr;
		int m_lastChannel = 0;
		int initial = 0;
		std::vector<int> order;
	};

	class Music {
	public:
		friend class AudioEngine;

		void play(int loops = 1);
		static void pause();
		static void stop();
		static void resume();

	private:
		Mix_Music* m_music = nullptr;
	};

	class AudioEngine
	{
	public:
		AudioEngine();
		~AudioEngine();

		void init();
		void destroy();

		SoundEffect loadSoundEffect(const std::string& filePath);
		Music loadMusic(const std::string& filePath);

	private:
		std::map<std::string, Mix_Chunk*> m_effectMap;
		std::map<std::string, Mix_Music*> m_musicMap;

		bool m_isInitialized = false;
	};

}