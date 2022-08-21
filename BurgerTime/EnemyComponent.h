#pragma once
#include <Component.h>
class EnemyComponent : public Component
{
public:
	EnemyComponent();
	~EnemyComponent() = default;

	void Update(float deltaTime, dae::GameObject* parentObject) override;
	void Initialize(float x, float y, int lives);

	void GetHit();
private:
	float m_XPos, m_YPos;
	int m_Lives;

	dae::GameObject* m_ParentObject;
};

