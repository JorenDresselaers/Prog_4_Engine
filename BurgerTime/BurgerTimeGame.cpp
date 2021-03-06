#include "BurgerTimeGame.h"

#include <Windows.h>

#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"

#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPS.h"
#include "LivesComponent.h"
#include "PlayerComponent.h"

using namespace dae;

BurgerTimeGame::BurgerTimeGame()
{
}

BurgerTimeGame::~BurgerTimeGame()
{
}

void BurgerTimeGame::LoadGame()
{
	auto& newScene = SceneManager::GetInstance().CreateScene("Demo");
	
	auto background = std::make_shared<GameObject>();
	auto logo = std::make_shared<GameObject>();
	auto text = std::make_shared<GameObject>();
	auto fps = std::make_shared<GameObject>();
	
	auto backgroundImage = ResourceManager::GetInstance().LoadTexture("background.jpg");
	auto logoImage = ResourceManager::GetInstance().LoadTexture("logo.png");
	auto pepperImage = ResourceManager::GetInstance().LoadTexture("Pepper_PH.png");
	
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
	pepper->AddComponent<PlayerComponent>();

	auto pepperTwo = std::make_shared<GameObject>();
	pepperTwo->AddComponent<PlayerComponent>()->SetPosition(200,200);
	
	InputManager::GetInstance().SetPlayer(pepper->GetComponent<PlayerComponent>());
	InputManager::GetInstance().SetPlayerTwo(pepperTwo->GetComponent<PlayerComponent>());

	newScene.Add(pepper);
	newScene.Add(pepperTwo);
	
	//AudioManager::GetInstance().Play("Farewell.wav", 100);
	//AudioManager::GetInstance().Play("Fishfight.wav", 100);
	//AudioManager::GetInstance().Play("Greeting1.wav", 100);
	//AudioManager::GetInstance().Play("Greeting2.wav", 100);

}