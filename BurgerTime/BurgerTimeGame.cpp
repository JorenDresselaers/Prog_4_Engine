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
#include "CollisionComponent.h"
#include "DeletionComponent.h"

using namespace dae;

BurgerTimeGame::BurgerTimeGame()
	: m_pTank{}
	, m_BlockSize{ 20 }
{
	InputManager::GetInstance().SetGame(this);
}

BurgerTimeGame::~BurgerTimeGame()
{
}

void BurgerTimeGame::LoadGame()
{
	std::cout << "\nLoading Burger Time";

	auto& newScene = SceneManager::GetInstance().CreateScene("Tron");

	LoadLevel();
	
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
	
	fps->AddComponent<FPS>()->SetPosition(0, 10);
	
	//newScene.Add(background);
	//newScene.Add(logo);
	//newScene.Add(text);
	newScene.Add(fps);
	
	//Actual game stuff
	auto tankImage = dae::ResourceManager::GetInstance().LoadTexture("Tank.png");
	
	auto tank = std::make_shared<GameObject>();
	tank->AddComponent<TextComponent>()->SetText("This is a tank");
	tank->GetComponent<TextComponent>()->SetPosition(200, 200);
	tank->AddComponent<RenderComponent>()->SetTexture(tankImage);
	tank->AddComponent<PlayerComponent>()->SetPosition(22,62);
	tank->AddComponent<CollisionComponent>()->Initialize(0, 0,
		tank->GetComponent<RenderComponent>()->GetWidth(),
		tank->GetComponent<RenderComponent>()->GetHeight(),
		CollisionType::PlayerTank
	);
	tank->AddComponent<DeletionComponent>();
	
	newScene.Add(tank);
	
	//AudioManager::GetInstance().Play("Farewell.wav", 100);
	//AudioManager::GetInstance().Play("Fishfight.wav", 100);
	//AudioManager::GetInstance().Play("Greeting1.wav", 100);
	//AudioManager::GetInstance().Play("Greeting2.wav", 100);
	m_pTank = tank.get();
}

void BurgerTimeGame::Update(float deltaTime)
{
	(void)deltaTime;

	std::vector<std::shared_ptr<GameObject>> collisionVector = SceneManager::GetInstance().GetCurrentScene().GetObjects();

	for (size_t currentObject{ 0 }; currentObject < collisionVector.size(); ++currentObject)
	{
		if (!collisionVector.at(currentObject)->GetComponent<CollisionComponent>())
		{
			collisionVector.erase(std::remove(collisionVector.begin(), collisionVector.end(), collisionVector.at(currentObject)), collisionVector.end());
		}
	}

	CollisionSide side = CollisionSide::Null;

	for (auto currentObject : collisionVector)
	{
		if (currentObject->GetComponent<DeletionComponent>())
		{
			for (auto objectToCheck : collisionVector)
			{
				auto collisionToCheck = objectToCheck->GetComponent<CollisionComponent>();
				if (collisionToCheck)
				{
					if (currentObject->GetComponent<CollisionComponent>()->isColliding(collisionToCheck, side))
					{
						currentObject->GetComponent<CollisionComponent>()->Collide(collisionToCheck, side);
					}
				}
				//if (float(pow((currentObject->GetComponent<CollisionComponent>()->GetX() - objectToCheck->GetComponent<CollisionComponent>()->GetX()), 2)
				//	+ pow((currentObject->GetComponent<CollisionComponent>()->GetY() - objectToCheck->GetComponent<CollisionComponent>()->GetY()), 2))
				//	< pow(m_BlockSize * 2, 2))
				//{
					//if (currentObject->GetComponent<CollisionComponent>()->isColliding(objectToCheck->GetComponent<CollisionComponent>(), side))
					//{
					//	currentObject->GetComponent<CollisionComponent>()->Collide(objectToCheck->GetComponent<CollisionComponent>(), side);
					//}
				//}
			}
		}
	}
}

void BurgerTimeGame::ProcessKeyUp(const SDL_KeyboardEvent& e)
{
	m_pTank->GetComponent<PlayerComponent>()->ProcessKeyUp(e);
}

void BurgerTimeGame::ProcessKeyDown(const SDL_KeyboardEvent& e)
{
	m_pTank->GetComponent<PlayerComponent>()->ProcessKeyDown(e);
}

void BurgerTimeGame::ProcessMouseUp(const SDL_MouseButtonEvent& e)
{
	m_pTank->GetComponent<PlayerComponent>()->ProcessMouseUp(e);
}

void BurgerTimeGame::ProcessMouseDown(const SDL_MouseButtonEvent& e)
{
	m_pTank->GetComponent<PlayerComponent>()->ProcessMouseDown(e);
}

void BurgerTimeGame::LoadLevel()
{
	m_LevelLoader.SetLevelSize(30, 28);
	m_LevelLoader.SetBlockSize(m_BlockSize);
	m_LevelLoader.LoadLevel("Level1.txt", "Tron");
}
