#pragma once
#include "Game.h"

class BurgerTimeGame final : public Game
{
public:
	BurgerTimeGame();
	~BurgerTimeGame();
	void LoadGame() override;
	void Run(float deltaTime);
private:
	GameObject* m_pPepper;
};

