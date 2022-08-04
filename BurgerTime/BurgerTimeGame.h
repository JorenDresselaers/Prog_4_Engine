#pragma once
#include "Game.h"

//disabling a warning in the sdl library because of level 4 warning level
#pragma warning( disable : 4201)
#pragma warning( disable : 26495)
#pragma warning( disable : 26812)

class BurgerTimeGame final : public Game
{
public:
	BurgerTimeGame();
	~BurgerTimeGame();
	void LoadGame() override;

	void LoadLevel();
private:
	//GameObject* m_pPepper;
};

