#pragma once
#include "Component.h"
#include "Command.h"
#include "RenderComponent.h"

class PlayerComponent : public Component
{
public:
	PlayerComponent();
	~PlayerComponent();

	void Update(float deltaTime) override;
	void Render() const override;
	std::string GetName() const override;

	void SetPosition(float x, float y);
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

private:
	float m_XPos;
	float m_YPos;

	float m_MovementSpeed;
	dae::RenderComponent* m_RenderComponent;
};

