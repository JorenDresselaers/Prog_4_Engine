#pragma once
#include "Component.h"
#include "Command.h"
#include "RenderComponent.h"
#include <SDL.h>

class PlayerComponent : public Component
{
public:
	PlayerComponent();
	~PlayerComponent();

	void Update(float deltaTime) override;
	void Render() const override;
	std::string GetName() const override;

	void ProcessInput(SDL_Event e);
	void SetKeys();
	void SetKeys(SDL_KeyCode up, SDL_KeyCode down, SDL_KeyCode left, SDL_KeyCode right);

	void SetPosition(float x, float y);
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

private:
	float m_XPos;
	float m_YPos;

	bool MovingLeft;
	bool MovingRight;
	bool MovingUp;
	bool MovingDown;

	SDL_KeyCode m_KeyUp;
	SDL_KeyCode m_KeyDown;
	SDL_KeyCode m_KeyLeft;
	SDL_KeyCode m_KeyRight;

	int m_MouseX;
	int m_MouseY;

	float m_MovementSpeed;
	dae::RenderComponent* m_RenderComponent;
};

