#pragma once
#include "Component.h"

enum class CollisionType
{
	Null,
	Wall,
	Bullet,
	PlayerTank,
	EnemyTank
};

class CollisionComponent final : public Component
{
public:
	CollisionComponent();
	~CollisionComponent() = default;

	//void Update(float deltaTime, dae::GameObject* parentObject) override;
	void SetPosition(float x, float y);

	void Initialize(float x, float y, float width, float height, CollisionType type);
	bool isColliding(float x, float y, float width, float height);
	bool isColliding(float x, float y);

	CollisionType GetType() const;

private:
	float m_X, m_Y, m_Width, m_Height;
	CollisionType m_CollisionType;
	int m_CollisionRange;
};

