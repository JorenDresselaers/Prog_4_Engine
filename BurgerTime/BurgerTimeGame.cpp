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
#include "BulletComponent.h"
#include "ScoreComponent.h"
#include "EnemyComponent.h"

#include "TronCommands.h"

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
	std::cout << "\nLoading Tron";

	//Loading the main game
	auto& newScene = SceneManager::GetInstance().CreateScene("Tron");

	LoadLevel();
	//
	//auto background = std::make_shared<GameObject>();
	//auto logo = std::make_shared<GameObject>();
	//auto text = std::make_shared<GameObject>();
	auto fps = std::make_shared<GameObject>();
	//	
	//auto backgroundImage = ResourceManager::GetInstance().LoadTexture("background.jpg");
	//auto logoImage = ResourceManager::GetInstance().LoadTexture("logo.png");
	//auto pepperImage = ResourceManager::GetInstance().LoadTexture("Pepper_PH.png");
	//
	//text->AddComponent<TextComponent>();
	//text->GetComponent<TextComponent>()->SetPosition(50, 100);
	//text->GetComponent<TextComponent>()->SetText("Test!");
	//
	//background->AddComponent<RenderComponent>()->SetTexture(backgroundImage);
	//logo->AddComponent<RenderComponent>()->SetTexture(logoImage);
	//
	fps->AddComponent<FPS>()->SetPosition(0, 10);
	
	//newScene.Add(background);
	//newScene.Add(logo);
	//newScene.Add(text);
	newScene.Add(fps);
	
	//Actual game stuff
	auto tankImage = dae::ResourceManager::GetInstance().LoadTexture("Tank.png");
	auto enemyTankImage = dae::ResourceManager::GetInstance().LoadTexture("EnemyTank.png");
	
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

	auto enemyTank = std::make_shared<GameObject>();
	enemyTank->AddComponent<RenderComponent>()->SetTexture(enemyTankImage);
	enemyTank->AddComponent<CollisionComponent>()->Initialize(0, 0,
		enemyTank->GetComponent<RenderComponent>()->GetWidth(),
		enemyTank->GetComponent<RenderComponent>()->GetHeight(),
		CollisionType::EnemyTank
	);
	enemyTank->AddComponent<ScoreComponent>()->SetScore(100);
	enemyTank->AddComponent<DeletionComponent>();
	enemyTank->AddComponent<EnemyComponent>()->Initialize(200,200, 3);
	
	newScene.Add(tank);
	newScene.Add(enemyTank);
	m_pTank = tank.get();

	//Loading menu
	auto& menuScene = SceneManager::GetInstance().CreateScene("Menu");

	auto background = std::make_shared<GameObject>();
	auto logo = std::make_shared<GameObject>();
	auto text = std::make_shared<GameObject>();
	auto menuFPS = std::make_shared<GameObject>();

	auto backgroundImage = ResourceManager::GetInstance().LoadTexture("background.jpg");
	auto logoImage = ResourceManager::GetInstance().LoadTexture("logo.png");

	text->AddComponent<TextComponent>();
	text->GetComponent<TextComponent>()->SetPosition(50, 100);
	text->GetComponent<TextComponent>()->SetText("Test!");

	background->AddComponent<RenderComponent>()->SetTexture(backgroundImage);
	logo->AddComponent<RenderComponent>()->SetTexture(logoImage);

	menuFPS->AddComponent<FPS>()->SetPosition(0, 10);

	menuScene.Add(background);
	menuScene.Add(logo);
	menuScene.Add(text);
	menuScene.Add(menuFPS);
	//menuScene.Add(tank);

	m_State = GameState::Menu;
	dae::InputManager::GetInstance().SetCommand(VK_PAD_DPAD_UP, new MoveUp(m_pTank));
	dae::InputManager::GetInstance().SetCommand(VK_PAD_DPAD_DOWN, new MoveDown(m_pTank));
	dae::InputManager::GetInstance().SetCommand(VK_PAD_DPAD_LEFT, new MoveLeft(m_pTank));
	dae::InputManager::GetInstance().SetCommand(VK_PAD_DPAD_RIGHT, new MoveRight(m_pTank));
	//dae::InputManager::GetInstance().SetCommand(VK_PAD_A, new MoveRight(m_pTank));
	//dae::InputManager::GetInstance().SetCommand(VK_PAD_B, new MoveLeft(m_pTank));
}

void BurgerTimeGame::Update(float deltaTime)
{
	(void)deltaTime;
	std::vector<std::shared_ptr<GameObject>> collisionVector;

	CollisionSide sideX = CollisionSide::Null;
	CollisionSide sideY = CollisionSide::Null;

	switch (m_State)
	{
	case GameState::Menu:
		break;
	case GameState::Running:
		collisionVector = SceneManager::GetInstance().GetCurrentScene().GetObjects();

		for (size_t currentObject{ 0 }; currentObject < collisionVector.size(); ++currentObject)
		{
			if (!collisionVector.at(currentObject)->GetComponent<CollisionComponent>())
			{
				collisionVector.erase(std::remove(collisionVector.begin(), collisionVector.end(), collisionVector.at(currentObject)), collisionVector.end());
			}
		}

		for (auto currentObject : collisionVector)
		{
			if (currentObject->GetComponent<DeletionComponent>())
			{
				for (auto objectToCheck : collisionVector)
				{
					sideX = CollisionSide::Null;
					sideY = CollisionSide::Null;

					auto collisionToCheck = objectToCheck->GetComponent<CollisionComponent>();
					if (collisionToCheck)
					{
						if (currentObject != objectToCheck)
						{
							if (!currentObject->GetComponent<BulletComponent>())
							{
								if (currentObject->GetComponent<CollisionComponent>()->isColliding(collisionToCheck, sideX, sideY))
								{
									currentObject->GetComponent<CollisionComponent>()->Collide(collisionToCheck, sideX, sideY);
								}
							}
							else
							{
								if (currentObject->GetComponent<CollisionComponent>()->isColliding(collisionToCheck, sideX))
								{
									currentObject->GetComponent<CollisionComponent>()->Collide(collisionToCheck, sideX, sideY);
								}
							}
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
		break;
	case GameState::End:
		break;
	default:
		break;
	}


}

void BurgerTimeGame::ProcessKeyUp(const SDL_KeyboardEvent& e)
{
	switch (m_State)
	{
	case GameState::Menu:
		break;
	case GameState::Running:
		m_pTank->GetComponent<PlayerComponent>()->ProcessKeyUp(e);
		break;
	case GameState::End:
		break;
	default:
		break;
	}
}

void BurgerTimeGame::ProcessKeyDown(const SDL_KeyboardEvent& e)
{
	switch (m_State)
	{
	case GameState::Menu:
		m_State = GameState::Running;
		SceneManager::GetInstance().SetScene("Tron");
		break;
	case GameState::Running:
		if (e.keysym.sym == SDLK_ESCAPE)
		{
			m_State = GameState::Menu;
			SceneManager::GetInstance().SetScene("Menu");
		}
		m_pTank->GetComponent<PlayerComponent>()->ProcessKeyDown(e);
		break;
	case GameState::End:
		break;
	default:
		break;
	}
}

void BurgerTimeGame::ProcessMouseUp(const SDL_MouseButtonEvent& e)
{
	switch (m_State)
	{
	case GameState::Menu:
		break;
	case GameState::Running:
		m_pTank->GetComponent<PlayerComponent>()->ProcessMouseUp(e);
		break;
	case GameState::End:
		break;
	default:
		break;
	}
}

void BurgerTimeGame::ProcessMouseDown(const SDL_MouseButtonEvent& e)
{
	switch (m_State)
	{
	case GameState::Menu:
		break;
	case GameState::Running:
		m_pTank->GetComponent<PlayerComponent>()->ProcessMouseDown(e);
		break;
	case GameState::End:
		break;
	default:
		break;
	}
}

void BurgerTimeGame::LoadLevel(const std::string& levelToLoad)
{
	m_LevelLoader.SetLevelSize(30, 28);
	m_LevelLoader.SetBlockSize(m_BlockSize);
	m_LevelLoader.LoadLevel(levelToLoad, "Tron");
}
