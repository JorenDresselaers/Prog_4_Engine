#pragma once
#include "Component.h"
#include "Command.h"
#include <SDL.h>
#include "GameObject.h"

class PlayerComponent final : public Component
{
public:
	PlayerComponent();
	~PlayerComponent();

	void Update(float deltaTime, dae::GameObject* parentObject) override;
	void Render() const override;

	void ProcessKeyUp(const SDL_KeyboardEvent& e);
	void ProcessKeyDown(const SDL_KeyboardEvent& e);
	void ProcessMouseUp(const SDL_MouseButtonEvent& e);
	void ProcessMouseDown(const SDL_MouseButtonEvent& e);

	void SetKeys();
	void SetKeys(SDL_KeyCode up, SDL_KeyCode down, SDL_KeyCode left, SDL_KeyCode right);

	void SetPosition(float x, float y);
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	void MoveUp(float deltaTime);
	void MoveDown(float deltaTime);
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void CollideUp();
	void CollideDown();
	void CollideLeft();
	void CollideRight();

	void GetHit();
	void SetLives(int newLives);
	int GetLives() const;
	void SetHasDied(bool b);
	bool GetHasDied() const;

	void AddScore(int score);
	int GetScore() const;
private:
	float m_XPos;
	float m_YPos;
	float m_MaxCooldown, m_CurrentCooldown;
	int m_Lives;

	bool MovingLeft;
	bool MovingRight;
	bool MovingUp;
	bool MovingDown;

	bool m_HasDied;

	SDL_KeyCode m_KeyUp;
	SDL_KeyCode m_KeyDown;
	SDL_KeyCode m_KeyLeft;
	SDL_KeyCode m_KeyRight;

	//int m_MouseX;
	//int m_MouseY;

	float m_MovementSpeed;
	float m_DeltaTime;
	int m_TotalScore;

	dae::GameObject* m_ParentObject;
};

