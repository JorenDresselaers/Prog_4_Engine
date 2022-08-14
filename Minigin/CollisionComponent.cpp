#include "MiniginPCH.h"
#include "CollisionComponent.h"

CollisionComponent::CollisionComponent()
	: m_CollisionType{CollisionType::Null}
	, m_X{ 0 }
	, m_Y{ 0 }
	, m_Width{ 0 }
	, m_Height{ 0 }
	, m_CollisionRange{ 100 }
{
}

//void CollisionComponent::Update(float deltaTime, dae::GameObject* parentObject)
//{
//	(void)deltaTime;
//}

void CollisionComponent::SetPosition(float x, float y)
{
	m_X = x;
	m_Y = y;
}

void CollisionComponent::Initialize(float x, float y, float width, float height, CollisionType type)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
	m_CollisionType = type;
}

bool CollisionComponent::isColliding(float x, float y, float width, float height)
{
	bool isColliding = false;

	if (x + width >= m_X &&
		x <= m_X + m_Width &&
		y + height >= m_Y &&
		y <= m_Y + m_Height)
	{
		isColliding = true;
	}

	return isColliding;
}

bool CollisionComponent::isColliding(float x, float y)
{
	bool isColliding = false;

	if (x >= m_X &&
		x <= m_X + m_Width &&
		y >= m_Y &&
		y <= m_Y + m_Height) 
	{
		isColliding = true;
	}

	return isColliding;
}

CollisionType CollisionComponent::GetType() const
{
	return m_CollisionType;
}
