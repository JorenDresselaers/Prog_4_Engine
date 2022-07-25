#include "MiniginPCH.h"
#include "AudioManager.h"

dae::AudioManager::AudioManager()
	: testSound{ nullptr }
	, m_DataPath{"../Data/"}
	, m_CurrentThreadCount{ 0 }
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
	std::cout << "\nEventQueue size: " << m_EventQueue.size();

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
	if (!m_EventQueue.empty() && m_CurrentThreadCount < m_EventQueue.size())
	{
		//std::cout << "\n\nProcessing sound:\nQueue size = " << m_EventQueue.size();
		//std::cout << "\nAmount of threads running = " << m_CurrentThreadCount;
		for (size_t i{ 0 }; i < m_EventQueue.size(); ++i)
		{
			std::cout << "\nStarting new thread";
			//std::string actualPath{ m_EventQueue.front().first.c_str() };
			//Mix_Chunk* newMusic = Mix_LoadWAV(actualPath.c_str());
			//newMusic->volume = Uint8(m_EventQueue.front().second);
			//if (newMusic) m_EventQueue.pop();
			//
			//Mix_PlayChannel(-1, newMusic, 0);

			m_CurrentThreadCount += 1;

			std::thread musicThread([this]()
				{
					//std::cout << "\nStarting new sound thread";
					m_Mutex.lock(); //locking m_EventQueue for threading
					if (m_EventQueue.size() > 0)
					{
						Mix_Chunk* newMusic = Mix_LoadWAV(m_EventQueue.front().first.c_str());
						int volume = m_EventQueue.front().second;

						if (newMusic)
						{
							std::cout << "\nPopping queue";
							m_EventQueue.pop();
							m_CurrentThreadCount--;
							m_Mutex.unlock();

							newMusic->volume = Uint8(volume);
							Mix_PlayChannel(-1, newMusic, 0);

							Sleep(3000);
							Mix_FreeChunk(newMusic);
						}
						else
						{
							std::cout << "\nFailed to load sound file";
							m_Mutex.unlock();
							m_CurrentThreadCount--;
						}
					}
					//m_EventQueue.pop();
					//m_Mutex.unlock();

					else
					{
						std::cout << "\nFailed to load sound file";
						m_Mutex.unlock();
						m_CurrentThreadCount--;
					}
					//std::cout << "\nEnding new sound thread";
				});

			musicThread.detach();
			//musicThread.join();
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
void dae::AudioManager::StopSound()
{
	Mix_HaltChannel(-1);
}

//void dae::AudioManager::StopAllSounds()
//{
//}
