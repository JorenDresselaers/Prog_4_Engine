#pragma once
#include "Singleton.h"
#include "SDL_mixer.h"

#include <iostream>
#include <mutex>
#include <queue>

namespace dae
{
	class AudioManager final : public Singleton<AudioManager>
	{
	public:
		AudioManager();
		virtual ~AudioManager();
		AudioManager(const AudioManager& other) = delete;
		AudioManager(AudioManager&& other) = delete;
		AudioManager& operator=(const AudioManager& other) = delete;
		AudioManager& operator=(AudioManager&& other) = delete;


		void Play(const std::string& filename, int volume);
		void Init(std::string path);

		//void PauseSound();
		void StopSound();
		//void StopAllSounds();

		void ProcessEventQueue();
	private:
		std::queue<std::pair<std::string, int>> m_EventQueue;
		//std::atomic<bool> m_IsRunning;
		std::thread m_Thread;
		std::mutex m_Mutex;

		Mix_Music* testSound;
		std::string m_DataPath;
		int m_CurrentThreadCount;

		void ThreadPlaySound(const std::string& filename, int volume);
	};
}
