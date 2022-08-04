#include "MiniginPCH.h"
#include "CollisionComponent.h"

CollisionComponent::CollisionComponent()
{
}

void CollisionComponent::Update(float deltaTime)
{
	(void)deltaTime;
}

void CollisionComponent::SetPosition(float x, float y)
{
	m_X = x;
	m_Y = y;
}

void CollisionComponent::Initialize(float x, float y, float width, float height)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
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
