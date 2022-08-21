#pragma once
#include "Component.h"
//#include "RenderComponent.h"

class BulletComponent final : public Component
{
public:
	BulletComponent();
	~BulletComponent();

	void Update(float deltaTime, dae::GameObject* parentObject) override;
	void Render() const override;

	bool CanBounce();
	void BounceY();
	void BounceX();
	void BounceLeft();
	void BounceRight();
	void BounceUp();
	void BounceDown();

	void Initialize(float originX, float originY, float targetX, float targetY, float xspeed, float yspeed, bool isPlayerBullet = false);
	float GetX() const;
	float GetY() const;
	bool GetIsPlayerBullet();
	void SetX(float x);
	void SetY(float y);

private:
	float m_XPos, m_YPos;
	float m_XSpeed, m_YSpeed;
	float m_DeltaTime, m_LifeTime, m_MaxLife;
	int m_Bounces, m_MaxBounces;
	bool m_IsPlayerBullet;

	//dae::RenderComponent* m_RenderComponent;

};

