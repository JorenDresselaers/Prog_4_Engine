#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"

#include <chrono>
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPS.h"
#include "LivesComponent.h"

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
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/*
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& newScene = SceneManager::GetInstance().CreateScene("Demo");

	auto background = std::make_shared<GameObject>();
	auto logo = std::make_shared<GameObject>();
	auto text = std::make_shared<GameObject>();
	auto fps = std::make_shared<GameObject>();

	auto backgroundImage = ResourceManager::GetInstance().LoadTexture("background.jpg");
	auto logoImage = ResourceManager::GetInstance().LoadTexture("logo.png");

	text->AddComponent<TextComponent>();
	text->GetComponent<TextComponent>()->SetPosition(50, 100);
	text->GetComponent<TextComponent>()->SetText("Test!");

	background->AddComponent<RenderComponent>()->SetTexture(backgroundImage);
	logo->AddComponent<RenderComponent>()->SetTexture(logoImage);

	fps->AddComponent<FPS>()->SetPosition(100, 100);
	
	newScene.Add(background);
	newScene.Add(logo);
	newScene.Add(text);
	newScene.Add(fps);

	//Actual game stuff

	auto pepper = std::make_shared<GameObject>();
	pepper->AddComponent<TextComponent>()->SetText("This is a pepper");
	pepper->GetComponent<TextComponent>()->SetPosition(200, 200);
	//pepper->AddComponent<LivesComponent>()->SetLives(3);

	newScene.Add(pepper);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	// todo: this update loop could use some work.
	bool doContinue = true;
	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag = 0.0f;
	//float fixedTimeStep{.5f};
	while (doContinue)
	{
		const auto start = chrono::high_resolution_clock::now();

		const auto currentTime = std::chrono::high_resolution_clock::now();
		float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;
		lag += deltaTime;

		doContinue = input.ProcessInput();

		while (lag >= MsPerFrame)
		{
			// fixedupdate(fixedtimestep);
			lag -= MsPerFrame;
		}

		sceneManager.Update(deltaTime);
		renderer.Render();

		const auto sleepTime = start + chrono::milliseconds(MsPerFrame)
			- chrono::high_resolution_clock::now();
		this_thread::sleep_for(sleepTime);
	}
	Cleanup();
}
