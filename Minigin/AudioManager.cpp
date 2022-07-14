#include "MiniginPCH.h"
#include "AudioManager.h"

dae::AudioManager::AudioManager()
	: testSound{ nullptr }
	, m_DataPath{"../Data/"}
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

dae::AudioManager::~AudioManager()
{
	Mix_Quit();
}

void dae::AudioManager::Play(const std::string& filename, int volume)
{
	m_EventQueue.push(std::pair<std::string, int>(m_DataPath + filename, volume));


	//temporary code to play file
	//std::string actualPath{ m_DataPath + filename };
	//
	//testSound = Mix_LoadMUS(actualPath.c_str());
	//
	//if (testSound != NULL )
	//{
	//	//testSound->volume = Uint8(volume);
	//	//Mix_PlayChannel(-1, testSound, 0);
	//	Mix_PlayMusic(testSound, volume);
	//}
	//else
	//{
	//	std::cout << "Failed to load sound! Error: " << Mix_GetError();
	//}
	//Mix_FreeChunk() to free sound effect
}

void dae::AudioManager::Init(std::string path)
{
	m_DataPath = path;
}

void dae::AudioManager::ProcessEventQueue()
{
	if (!m_EventQueue.empty())
	{
		for (size_t i{ 0 }; i < m_EventQueue.size(); ++i)
		{
			//std::string actualPath{ m_EventQueue.front().first.c_str() };
			//Mix_Chunk* newMusic = Mix_LoadWAV(actualPath.c_str());
			//newMusic->volume = Uint8(m_EventQueue.front().second);
			//if (newMusic) m_EventQueue.pop();
			//
			//Mix_PlayChannel(-1, newMusic, 0);


			std::thread musicThread([this]()
				{
					//std::cout << "\nStarting new sound thread";
					m_Mutex.lock(); //locking m_EventQueue for threading

					Mix_Chunk* newMusic = Mix_LoadWAV(m_EventQueue.front().first.c_str());
					int volume = m_EventQueue.front().second;
					if (newMusic)
					{
						m_EventQueue.pop();
						newMusic->volume = Uint8(volume);

						m_Mutex.unlock();
						Mix_PlayChannel(-1, newMusic, 0);
					}
					else
					{
						m_Mutex.unlock();
					}
					//std::cout << "\nEnding new sound thread";
				});
			musicThread.join();
		}
	}
}

void dae::AudioManager::ThreadPlaySound(const std::string& filename, int volume)
{
	Mix_Chunk* newMusic = Mix_LoadWAV(filename.c_str());
	newMusic->volume = Uint8(volume);

	Mix_PlayChannel(-1, newMusic, 0);
	//Mix_PlayChannelTimed(-1, newMusic, 1, -1);
	
}

//void dae::AudioManager::PauseSound()
//{
//}
//
//void dae::AudioManager::StopSound()
//{
//}
//
//void dae::AudioManager::StopAllSounds()
//{
//}
