#include "LevelLoader.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include <fstream>
#include <iostream>
#include "ResourceManager.h"
#include "SceneManager.h"
#include "PlayerComponent.h"

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
	std::cout << "\nLoading level " << levelFile;
	m_LevelFile.open("../Data/" + levelFile);
	if (m_LevelFile.is_open()) {
		std::cout << "\nLevel loading";

		auto wallImage = dae::ResourceManager::GetInstance().LoadTexture("wall.png");

		char c{};

		for (int y{ 0 }; y <= m_LevelSizeY; ++y)
		{
			for (int x{ 0 }; x <= m_LevelSizeX; ++x)
			{
				c = char(m_LevelFile.get());
				//std::cout << "\nChecking block [" << x << ", " << y << "]";
				//std::cout << "\nCharacter at block: " << c;

				if (c != 10)
				{
					switch (c)
					{
					case 'X':
						//std::cout << "\nAdding new wall";
						auto newObject = std::make_shared<dae::GameObject>();

						newObject->AddComponent<dae::RenderComponent>()->SetTexture(wallImage);
						newObject->GetComponent<dae::RenderComponent>()->SetPosition(float(x * m_BlockSize), float(y * m_BlockSize + m_LevelOffsetY));
						newObject->GetComponent<dae::RenderComponent>()->SetDimensions(float(m_BlockSize), float(m_BlockSize));
						newObject->AddComponent<CollisionComponent>()->Initialize(float(x * m_BlockSize), float(y * m_BlockSize + m_LevelOffsetY), float(m_BlockSize), float(m_BlockSize), CollisionType::Wall);

						dae::SceneManager::GetInstance().GetCurrentScene().Add(newObject);
						break;
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
		}
		return true;
	}
	return false;
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
