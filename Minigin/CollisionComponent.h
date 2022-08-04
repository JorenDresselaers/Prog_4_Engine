#pragma once
#include "Component.h"
class CollisionComponent final : public Component
{
public:
	CollisionComponent();
	~CollisionComponent() = default;

	void Update(float deltaTime) override;
	void SetPosition(float x, float y);

	void Initialize(float x, float y, float width, float height);
	bool isColliding(float x, float y, float width, float height);
	bool isColliding(float x, float y);

private:
	float m_X, m_Y, m_Width, m_Height;
};

