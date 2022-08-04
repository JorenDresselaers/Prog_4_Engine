#pragma once
#include "Component.h"
#include "RenderComponent.h"

class BulletComponent final : public Component
{
public:
	BulletComponent();
	~BulletComponent();

	void Update(float deltaTime) override;
	void Render() const override;

	void Initialize(float originX, float originY, float targetX, float targetY, float xspeed, float yspeed);
	float GetX() const;
	float GetY() const;
private:
	float m_XPos, m_YPos;
	float m_XSpeed, m_YSpeed;
	int m_Bounces, m_MaxBounces;

	//dae::RenderComponent* m_RenderComponent;

};

