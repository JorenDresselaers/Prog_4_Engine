#pragma once
#include "SDL.h"

class Game
{
public:
	Game() = default;
	virtual ~Game() = default;
	Game(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game& operator=(Game&& other) = delete;


	virtual void LoadGame();

	virtual void Update(float deltaTime);

	virtual void ProcessKeyUp(const SDL_KeyboardEvent& e);
	virtual void ProcessKeyDown(const SDL_KeyboardEvent& e);
	virtual void ProcessMouseUp(const SDL_MouseButtonEvent& e);
	virtual void ProcessMouseDown(const SDL_MouseButtonEvent& e);
};

