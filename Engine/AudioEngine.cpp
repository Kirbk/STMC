#include "AudioEngine.h"
#include "EngineErrors.h"
#include <iostream>
#include <algorithm>

namespace Engine{

	SoundEffect::SoundEffect() {
		order = {8, 8, 8, 8, 8, 8, 8, 8};
	}

	void SoundEffect::play(int loops) {
		m_lastChannel = Mix_PlayChannel(-1, m_chunk, loops);
		if (order[0] == 8) {
			order.erase(order.begin());
		}
		//if (!order.empty()) std::cout << order[0] << std::endl;

		if (m_lastChannel == -1) {


			if (Mix_PlayChannel(order[0], m_chunk, loops) == -1) {
				if (Mix_PlayChannel(0, m_chunk, loops) == -1) {
					fatalError("Mix_PlayChannel error: " + std::string(Mix_GetError()));
				}
			}

			order.push_back(order[0]);
			order.erase(order.begin());
		}
		else {
			order.erase(std::remove(order.begin(), order.end(), m_lastChannel), order.end());
			order.push_back(m_lastChannel);
		}

		for (int i = 0; i < order.size(); i++) {
			std::cout << order[i];
		}
		std::cout << std::endl;
	}

	void Music::play(int loops) {
		Mix_PlayMusic(m_music, loops);
	}

	void Music::pause() {
		Mix_PauseMusic();
	}

	void Music::stop() {
		Mix_HaltMusic();
	}

	void Music::resume() {
		Mix_ResumeMusic();
	}

	AudioEngine::AudioEngine()
	{
	}


	AudioEngine::~AudioEngine()
	{
		destroy();
	}

	void AudioEngine::init() {
		if (m_isInitialized) {
			fatalError("Tried to initialize audio engine twice\n");
		}

		if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1) {
			fatalError("Mix_Init error: " + std::string(Mix_GetError()));
		}

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
			fatalError("Mix_OpenAudio error: " + std::string(Mix_GetError()));
		}

		m_isInitialized = true;
	}

	void AudioEngine::destroy() {
		if (m_isInitialized) {
			m_isInitialized = false;

			for (auto& it : m_effectMap) {
				Mix_FreeChunk(it.second);
			}

			for (auto& it : m_musicMap) {
				Mix_FreeMusic(it.second);
			}

			Mix_CloseAudio();
			Mix_Quit();
		}
	}

	SoundEffect AudioEngine::loadSoundEffect(const std::string& filePath) {
		auto it = m_effectMap.find(filePath);
		
		SoundEffect effect;

		if (it == m_effectMap.end()) {
			Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
			if (chunk == nullptr)
				fatalError("Mix_LoadWAV error: " + std::string(Mix_GetError()));

			effect.m_chunk = chunk;
			m_effectMap[filePath] = chunk;
		}
		else {
			effect.m_chunk = it->second;
		}

		return effect;
	}
	
	Music AudioEngine::loadMusic(const std::string& filePath) {
		auto it = m_musicMap.find(filePath);

		Music music;

		if (it == m_musicMap.end()) {
			Mix_Music* mixMusic = Mix_LoadMUS(filePath.c_str());
			if (mixMusic == nullptr)
				fatalError("Mix_LoadMusic error: " + std::string(Mix_GetError()));

			music.m_music = mixMusic;
			m_musicMap[filePath] = mixMusic;
		}
		else {
			music.m_music = it->second;
		}

		return music;
	}

}