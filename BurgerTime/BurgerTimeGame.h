#pragma once
#include "Game.h"
#include "LevelLoader.h"


//disabling a warning in the sdl library because of level 4 warning level
#pragma warning( disable : 4201)
#pragma warning( disable : 26495)
#pragma warning( disable : 26812)

namespace dae
{
	class GameObject;
}

class BurgerTimeGame final : public Game
{
public:
	BurgerTimeGame();
	~BurgerTimeGame();
	void LoadGame() override;

	void Update(float deltaTime) override;

	void ProcessKeyUp(const SDL_KeyboardEvent& e) override;
	void ProcessKeyDown(const SDL_KeyboardEvent& e) override;
	void ProcessMouseUp(const SDL_MouseButtonEvent& e) override;
	void ProcessMouseDown(const SDL_MouseButtonEvent& e) override;

	void LoadLevel();
private:
	dae::GameObject* m_pTank;
	LevelLoader m_LevelLoader;
	int m_BlockSize ;
};

