#pragma once
#include "Game.h"

//disabling a warning in the sdl library because of level 4 warning level
#pragma warning( disable : 4201 )

class BurgerTimeGame final : public Game
{
public:
	BurgerTimeGame();
	~BurgerTimeGame();
	void LoadGame() override;
private:
	//GameObject* m_pPepper;
};

