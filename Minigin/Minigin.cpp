#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"

#include <chrono>
#include <time.h>
#include "Game.h"

using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		600,
		600,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

bool dae::Minigin::SetGame(Game* newGame)
{
	if (!m_Game)
	{
		m_Game = newGame;
		return true;
	}
	return false;
}

void dae::Minigin::Cleanup()
{
	//delete m_Game;
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();
	srand(unsigned int(time(NULL)));

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	AudioManager::GetInstance().Init("../Data/");
	
	if (m_Game)
	{
		m_Game->LoadGame();
	}

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& sound = AudioManager::GetInstance();

	// todo: this update loop could use some work.
	bool doContinue = true;
	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag = 0.0f;
	//float fixedTimeStep{.5f};
	std::cout << "\nStarting Game Loop";
	while (doContinue)
	{
		const auto start = chrono::high_resolution_clock::now();

		const auto currentTime = std::chrono::high_resolution_clock::now();
		float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;
		lag += deltaTime;

		doContinue = input.ProcessInput();

		//while (lag >= MsPerFrame)
		//{
		//	// fixedupdate(fixedtimestep);
		//	lag -= MsPerFrame;
		//}

		m_Game->Update(deltaTime);
		sceneManager.Update(deltaTime);
		renderer.Render();
		sound.ProcessEventQueue();

		const auto sleepTime = start + chrono::milliseconds(MsPerFrame)
			- chrono::high_resolution_clock::now();
		this_thread::sleep_for(sleepTime);
	}
	Cleanup();
}
