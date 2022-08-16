#pragma once
#include "SDL.h"

class Game
{
public:
	virtual ~Game() = default;
	virtual void LoadGame();

	virtual void Update(float deltaTime);

	virtual void ProcessKeyUp(const SDL_KeyboardEvent& e);
	virtual void ProcessKeyDown(const SDL_KeyboardEvent& e);
	virtual void ProcessMouseUp(const SDL_MouseButtonEvent& e);
	virtual void ProcessMouseDown(const SDL_MouseButtonEvent& e);
};

