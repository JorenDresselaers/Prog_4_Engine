#include "TronGame.h"

#include <Windows.h>

#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include "ScoreManager.h"
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
#include <fstream>
#include <iostream>

using namespace dae;

TronGame::TronGame()
	: m_pTank{}
	, m_BlockSize{ 20 }
{
	InputManager::GetInstance().SetGame(this);
}

TronGame::~TronGame()
{
}

void TronGame::LoadGame()
{
	std::cout << "\nLoading Tron";

	//Loading the main game
	auto& newScene = SceneManager::GetInstance().CreateScene("Tron1");

	LoadLevel();
	auto fps = std::make_shared<GameObject>();
	fps->AddComponent<FPS>()->SetPosition(0, 10);
	
	newScene.Add(fps);
	
	//Actual game stuff
	auto tankImage = dae::ResourceManager::GetInstance().LoadTexture("Tank.png");
	auto enemyTankImage = dae::ResourceManager::GetInstance().LoadTexture("EnemyTank.png");
	
	auto tank = std::make_shared<GameObject>();
	tank->AddComponent<TextComponent>()->SetText("This is a tank");
	tank->GetComponent<TextComponent>()->SetPosition(200, 10);
	tank->AddComponent<RenderComponent>()->SetTexture(tankImage);
	tank->AddComponent<PlayerComponent>()->SetPosition(22,62);
	tank->AddComponent<CollisionComponent>()->Initialize(0, 0,
		tank->GetComponent<RenderComponent>()->GetWidth(),
		tank->GetComponent<RenderComponent>()->GetHeight(),
		CollisionType::PlayerTank
	);
	tank->AddComponent<DeletionComponent>();
	
	newScene.Add(tank);
	m_pTank = tank;

	LoadMenuScene();
	m_State = GameState::Menu;

	SetCommands();

}

void TronGame::Update(float deltaTime)
{
	(void)deltaTime;
	std::vector<std::shared_ptr<GameObject>> collisionVector;

	CollisionSide sideX = CollisionSide::Null;
	CollisionSide sideY = CollisionSide::Null;
	bool loadNextLevel{ false };

	switch (m_State)
	{
	case GameState::Menu:
		break;
	case GameState::Running:
		collisionVector = SceneManager::GetInstance().GetCurrentScene().GetObjects();
		loadNextLevel = true;

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
				//handling collision
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
				}

				//handling enemies and progressing through levels
				if (currentObject->GetComponent<EnemyComponent>())
				{
					loadNextLevel = false;
				}

				//if (currentObject->GetComponent<DeletionComponent>()->GetCanDelete() && currentObject->GetComponent<ScoreComponent>())
				//{
				//	std::cout << "\nAdding score";
				//	m_pTank->GetComponent<PlayerComponent>()->AddScore(currentObject->GetComponent<ScoreComponent>()->GetScore());
				//}
			}
		}

		if (m_pTank->GetComponent<PlayerComponent>()->GetHasDied())
		{
			m_pTank->GetComponent<PlayerComponent>()->SetHasDied(false);
			m_pTank->GetComponent<PlayerComponent>()->SetPosition(22, 62);
		}

		if (m_pTank->GetComponent<PlayerComponent>()->GetLives() <= 0)
		{
			m_State = GameState::End;
			LoadEndScene();
		}

		if (loadNextLevel)
		{
			++m_LevelsPassed;
			std::cout << "\nLoading new level";
			SceneManager::GetInstance().CreateScene("Tron" + std::to_string(m_LevelsPassed + 1));
			m_LevelLoader.LoadNextLevel(SceneManager::GetInstance().GetCurrentSceneString());
			
			m_pTank->GetComponent<PlayerComponent>()->SetPosition(22, 62);
			SceneManager::GetInstance().GetCurrentScene().Add(m_pTank);
		}
		break;
	case GameState::End:
		break;
	default:
		break;
	}


}

void TronGame::ProcessKeyUp(const SDL_KeyboardEvent& e)
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

void TronGame::ProcessKeyDown(const SDL_KeyboardEvent& e)
{
	switch (m_State)
	{
	case GameState::Menu:
		m_State = GameState::Running;
		SceneManager::GetInstance().SetScene("Tron" + std::to_string(m_LevelsPassed + 1));
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

void TronGame::ProcessMouseUp(const SDL_MouseButtonEvent& e)
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

void TronGame::ProcessMouseDown(const SDL_MouseButtonEvent& e)
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

void TronGame::LoadLevel(const std::string& levelToLoad)
{
	std::cout << "\nLoading scene " << "Tron" + std::to_string(m_LevelsPassed + 1);
	m_LevelLoader.SetLevelSize(30, 28);
	m_LevelLoader.SetBlockSize(m_BlockSize);
	m_LevelLoader.LoadLevel(levelToLoad, "Tron" + std::to_string(m_LevelsPassed + 1));
}

void TronGame::LoadMenuScene()
{
	auto& menuScene = SceneManager::GetInstance().CreateScene("Menu");

	auto background = std::make_shared<GameObject>();
	auto text = std::make_shared<GameObject>();

	auto backgroundImage = ResourceManager::GetInstance().LoadTexture("tron-main-menu.jpg");

	text->AddComponent<TextComponent>();
	text->GetComponent<TextComponent>()->SetPosition(175, 175);
	text->GetComponent<TextComponent>()->SetText("Press any key to begin the game!");

	background->AddComponent<RenderComponent>()->SetTexture(backgroundImage);
	background->GetComponent<RenderComponent>()->SetDimensions(float(600), float(600));

	menuScene.Add(background);
	menuScene.Add(text);
}

void TronGame::LoadEndScene()
{
	auto& menuScene = SceneManager::GetInstance().CreateScene("End");

	auto background = std::make_shared<GameObject>();
	auto text = std::make_shared<GameObject>();

	auto backgroundImage = ResourceManager::GetInstance().LoadTexture("background.jpg");

	background->AddComponent<RenderComponent>()->SetTexture(backgroundImage);
	background->GetComponent<RenderComponent>()->SetDimensions(float(600), float(600));

	menuScene.Add(background);

	std::string name;
	std::cout << "\nPlease enter your name: ";
	std::getline(std::cin, name);

	//checking high score file
	std::fstream highscoreFile;
	highscoreFile.open("../Data/Highscores.txt");

	std::vector<int> highscores;
	std::vector<std::string> players;
	int newScore{ ScoreManager::GetInstance().GetScore() };
	bool addingNewScore{ false };
	bool addedNewScore{ false };
	bool fileOpened{ false };
	int scoresSeen{ 0 };

	if (highscoreFile.is_open())
	{
		int nameOrScore{ 0 }; // 1 = score | 0 = name
		for (std::string line; std::getline(highscoreFile, line); )
		{
			++nameOrScore;
			nameOrScore%=2;
			if (scoresSeen < 19)
			{
				//std::cout << "\n " << scoresSeen;
				++scoresSeen;
				if (nameOrScore == 0)
				{
					if (addingNewScore && !addedNewScore)
					{
						++scoresSeen;

						players.push_back(name);
						players.push_back(line);
						std::cout << "Player: " << name << std::endl;
						addingNewScore = false;
						addedNewScore = true;
					}
					else
					{
						std::cout << "Player: " << line << std::endl;
						players.push_back(line);
					}
				}
				else
				{
					int oldScore{ std::stoi(line) };
					if (newScore > oldScore && !addedNewScore)
					{
						highscores.push_back(newScore);
						highscores.push_back(std::stoi(line));
						addingNewScore = true;
						std::cout << "Score: " << newScore << std::endl;
					}
					else
					{
						std::cout << "Score: " << line << std::endl;
						highscores.push_back(oldScore);
					}
				}
			}
		}

		if (scoresSeen < 19 && !addingNewScore && !addedNewScore)
		{
			highscores.push_back(newScore);
			players.push_back(name);
			std::cout<< "Score: " << newScore << std::endl << "Player: " << name << std::endl;
		}

		for (int i{ 0 }; i < highscores.size(); ++i)
		{
			std::shared_ptr<GameObject> newTextPlayer = std::make_shared<GameObject>();
			newTextPlayer->AddComponent<TextComponent>()->SetText(players.at(i));
			newTextPlayer->GetComponent<TextComponent>()->SetPosition(100.f, float(100 + 40 * i));

			std::shared_ptr<GameObject> newTextScore = std::make_shared<GameObject>();
			newTextScore->AddComponent<TextComponent>()->SetText(std::to_string(highscores.at(i)));
			newTextScore->GetComponent<TextComponent>()->SetPosition(100.f, float(120 + 40 * i));

			SceneManager::GetInstance().GetCurrentScene().Add(newTextPlayer);
			SceneManager::GetInstance().GetCurrentScene().Add(newTextScore);

		}
		highscoreFile.close();
		fileOpened = true;
	}

	if (fileOpened)
	{
		std::ofstream highscoreFileWrite;

		highscoreFileWrite.open("../Data/Highscores.txt", std::ios::trunc);

		if (highscoreFileWrite.is_open())
		{
			for (int i{ 0 }; i < highscores.size(); ++i)
			{
				highscoreFileWrite << std::to_string(highscores.at(i)) << std::endl << players.at(i) << std::endl;
			}
			highscoreFileWrite.close();
		}
	}
}

void TronGame::SetCommands()
{
	dae::InputManager::GetInstance().SetCommand(VK_PAD_DPAD_UP, new MoveUp(m_pTank.get()));
	dae::InputManager::GetInstance().SetCommand(VK_PAD_DPAD_DOWN, new MoveDown(m_pTank.get()));
	dae::InputManager::GetInstance().SetCommand(VK_PAD_DPAD_LEFT, new MoveLeft(m_pTank.get()));
	dae::InputManager::GetInstance().SetCommand(VK_PAD_DPAD_RIGHT, new MoveRight(m_pTank.get()));
	dae::InputManager::GetInstance().SetCommand(VK_PAD_A, new MoveRight(m_pTank.get()));
	dae::InputManager::GetInstance().SetCommand(VK_PAD_B, new MoveLeft(m_pTank.get()));
}
