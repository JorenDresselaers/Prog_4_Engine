#include "LevelLoader.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include <fstream>
#include <iostream>
#include "ResourceManager.h"
#include "SceneManager.h"
#include "PlayerComponent.h"
#include "EnemyComponent.h"
#include "DeletionComponent.h"
#include "ScoreComponent.h"
#include "FPS.h"

LevelLoader::LevelLoader()
	: m_BlockSize{ 20 }
	, m_LevelSizeX{ 0 }
	, m_LevelSizeY{ 0 }
	, m_LevelOffsetY{ m_BlockSize*2 }
{
}

LevelLoader::~LevelLoader()
{
}

bool LevelLoader::LoadLevel(std::string levelFile, std::string scene)
{
	auto fps = std::make_shared<dae::GameObject>();
	fps->AddComponent<dae::FPS>()->SetPosition(0, 10);

	dae::SceneManager::GetInstance().GetCurrentScene().Add(fps);
	std::cout << "\nLoading level " << levelFile;
	m_LevelFile.open("../Data/" + levelFile);
	if (m_LevelFile.is_open()) {
		//std::cout << "\nLevel loading";

		auto wallImage = dae::ResourceManager::GetInstance().LoadTexture("wall.png");
		auto enemyTankImage = dae::ResourceManager::GetInstance().LoadTexture("EnemyTank.png");
		auto crystalImage = dae::ResourceManager::GetInstance().LoadTexture("crystal.png");
		auto recogniserImage = dae::ResourceManager::GetInstance().LoadTexture("Recogniser.png");

		char c{};
		std::string firstLine;
		std::getline(m_LevelFile, firstLine);
		m_NextLevel = firstLine;

		for (int y{ 0 }; y <= m_LevelSizeY; ++y)
		{
			for (int x{ 0 }; x <= m_LevelSizeX; ++x)
			{
				c = char(m_LevelFile.get());
				//std::cout << "\nChecking block [" << x << ", " << y << "]";
				//std::cout << "\nCharacter at block: " << c;

				if (c != 10)
				{
					if (c == 'X')
					{
						std::shared_ptr<dae::GameObject> newObject = std::make_shared<dae::GameObject>();

						newObject->AddComponent<dae::RenderComponent>()->SetTexture(wallImage);
						newObject->GetComponent<dae::RenderComponent>()->SetPosition(float(x * m_BlockSize), float(y * m_BlockSize + m_LevelOffsetY));
						newObject->GetComponent<dae::RenderComponent>()->SetDimensions(float(m_BlockSize), float(m_BlockSize));
						newObject->AddComponent<CollisionComponent>()->Initialize(float(x * m_BlockSize), float(y * m_BlockSize + m_LevelOffsetY), float(m_BlockSize), float(m_BlockSize), CollisionType::Wall);

						dae::SceneManager::GetInstance().GetCurrentScene().Add(newObject);
					}
					else if (c == 'E')
					{
						std::shared_ptr<dae::GameObject> enemyTank = std::make_shared<dae::GameObject>();
						enemyTank->AddComponent<dae::RenderComponent>()->SetTexture(enemyTankImage);
						enemyTank->AddComponent<CollisionComponent>()->Initialize(0, 0,
							enemyTank->GetComponent<dae::RenderComponent>()->GetWidth(),
							enemyTank->GetComponent<dae::RenderComponent>()->GetHeight(),
							CollisionType::EnemyTank
						);
						enemyTank->AddComponent<ScoreComponent>()->SetScore(100);
						enemyTank->AddComponent<DeletionComponent>();

						//+2.5 is to center the tanks on the blocks they spawn on
						enemyTank->AddComponent<EnemyComponent>()->Initialize(float(x * m_BlockSize + 2.5), float(y * m_BlockSize + m_LevelOffsetY + 2.5), 3);

						dae::SceneManager::GetInstance().GetCurrentScene().Add(enemyTank);
					}
					else if (c == 'C')
					{
						std::shared_ptr<dae::GameObject> crystal = std::make_shared<dae::GameObject>();

						crystal->AddComponent<dae::RenderComponent>()->SetTexture(crystalImage);
						crystal->GetComponent<dae::RenderComponent>()->SetPosition(
							float(x * m_BlockSize + 2.5),
							float(y * m_BlockSize + m_LevelOffsetY + 2.5));

						crystal->AddComponent<CollisionComponent>()->Initialize(
							float(x * m_BlockSize + 2.5),
							float(y * m_BlockSize + m_LevelOffsetY + 2.5),
							crystal->GetComponent<dae::RenderComponent>()->GetWidth(),
							crystal->GetComponent<dae::RenderComponent>()->GetHeight(),
							CollisionType::Crystal
						);

						dae::SceneManager::GetInstance().GetCurrentScene().Add(crystal);
					}
					else if (c == 'R')
					{
						std::shared_ptr<dae::GameObject> Recogniser = std::make_shared<dae::GameObject>();
						Recogniser->AddComponent<dae::RenderComponent>()->SetTexture(recogniserImage);
						Recogniser->AddComponent<CollisionComponent>()->Initialize(0, 0,
							Recogniser->GetComponent<dae::RenderComponent>()->GetWidth(),
							Recogniser->GetComponent<dae::RenderComponent>()->GetHeight(),
							CollisionType::EnemyTank
						);
						Recogniser->AddComponent<ScoreComponent>()->SetScore(250);
						Recogniser->AddComponent<DeletionComponent>();

						//+2.5 is to center the tanks on the blocks they spawn on
						Recogniser->AddComponent<EnemyComponent>()->Initialize(float(x * m_BlockSize + 2.5), float(y * m_BlockSize + m_LevelOffsetY + 2.5), 3);

						dae::SceneManager::GetInstance().GetCurrentScene().Add(Recogniser);
					}


					//switch (c)
					//{
					//case 'X':
					//	//std::cout << "\nAdding new wall";
					//	std::shared_ptr<dae::GameObject> newObject = std::make_shared<dae::GameObject>();
					//
					//	newObject->AddComponent<dae::RenderComponent>()->SetTexture(wallImage);
					//	newObject->GetComponent<dae::RenderComponent>()->SetPosition(float(x * m_BlockSize), float(y * m_BlockSize + m_LevelOffsetY));
					//	newObject->GetComponent<dae::RenderComponent>()->SetDimensions(float(m_BlockSize), float(m_BlockSize));
					//	newObject->AddComponent<CollisionComponent>()->Initialize(float(x * m_BlockSize), float(y * m_BlockSize + m_LevelOffsetY), float(m_BlockSize), float(m_BlockSize), CollisionType::Wall);
					//
					//	dae::SceneManager::GetInstance().GetCurrentScene().Add(newObject);
					//	break;
					//case 'E':
					//
					//	std::shared_ptr<dae::GameObject> enemyTank = std::make_shared<dae::GameObject>();
					//	enemyTank->AddComponent<dae::RenderComponent>()->SetTexture(enemyTankImage);
					//	enemyTank->AddComponent<CollisionComponent>()->Initialize(0, 0,
					//		enemyTank->GetComponent<dae::RenderComponent>()->GetWidth(),
					//		enemyTank->GetComponent<dae::RenderComponent>()->GetHeight(),
					//		CollisionType::EnemyTank
					//	);
					//	enemyTank->AddComponent<ScoreComponent>()->SetScore(100);
					//	enemyTank->AddComponent<DeletionComponent>();
					//	enemyTank->AddComponent<EnemyComponent>()->Initialize(200, 200, 3);
					//
					//	dae::SceneManager::GetInstance().GetCurrentScene().Add(enemyTank);
					//	break;
					//case 'P':
					//	auto tankImage = dae::ResourceManager::GetInstance().LoadTexture("Tank.png");
					//
					//	//tank->AddComponent<dae::TextComponent>()->SetText("This is a tank");
					//	//tank->GetComponent<TextComponent>()->SetPosition(200, 200);
					//	newObject->AddComponent<dae::RenderComponent>()->SetTexture(tankImage);
					//	newObject->AddComponent<PlayerComponent>();
					//	break;
				}
			}
		}
		m_LevelFile.close();
		return true;
	}
	return false;
}

bool LevelLoader::LoadNextLevel(std::string scene)
{
	return LoadLevel(m_NextLevel, scene);
}

void LevelLoader::SetLevelSize(int x, int y)
{
	m_LevelSizeX = x;
	m_LevelSizeY = y;
}

void LevelLoader::SetBlockSize(int newSize)
{
	m_BlockSize = newSize;
}
