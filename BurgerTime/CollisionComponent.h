#pragma once
#include "Component.h"
#include <memory>

namespace dae
{
	class GameObject;
}

enum class CollisionType
{
	Null,
	Wall,
	Bullet,
	PlayerTank,
	EnemyTank
};

enum class CollisionSide
{
	Right,
	Left,
	Up,
	Down,
	Null
};

class CollisionComponent final : public Component
{
public:
	CollisionComponent();
	~CollisionComponent() = default;

	void Update(float deltaTime, dae::GameObject* parentObject) override;
	void SetPosition(float x, float y);
	void Collide(std::shared_ptr<CollisionComponent> other, const CollisionSide& side);

	void Initialize(float x, float y, float width, float height, CollisionType type);
	bool isColliding(float x, float y, float width, float height);
	bool isColliding(float x, float y);
	bool isColliding(std::shared_ptr<CollisionComponent> other, CollisionSide& side);

	CollisionType GetType() const;
	void SetType(CollisionType newType);

	float GetX();
	float GetY();

private:
	float m_X, m_Y, m_Width, m_Height;
	CollisionType m_CollisionType;
	int m_CollisionRange;
	dae::GameObject* m_ParentObject;
};

