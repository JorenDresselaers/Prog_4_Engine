#pragma once
#include "Component.h"

class LivesComponent : Component
{
public:
	LivesComponent(int currentLives);
	~LivesComponent() = default;

	void Update(float deltaTime) override;

	void GainLife();
	void LoseLife();
	void SetLives(int newLives);

private:
	int m_Lives;

};

