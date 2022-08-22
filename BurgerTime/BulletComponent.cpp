#include "BulletComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "DeletionComponent.h"

BulletComponent::BulletComponent()
	: m_XPos{ 0 }
	, m_YPos{ 0 }
	, m_XSpeed{ 0 }
	, m_YSpeed{ 0 }
	, m_Bounces{ 0 }
	, m_MaxBounces{ 5 }
	, m_DeltaTime{ 0 }
	, m_IsPlayerBullet{ false }
	, m_LifeTime{ 0 }
	, m_MaxLife{ 5 }
{
}

BulletComponent::~BulletComponent()
{
}

void BulletComponent::Update(float deltaTime, dae::GameObject* parentObject)
{
	m_DeltaTime = deltaTime;
	m_LifeTime += deltaTime;
	if (m_LifeTime >= m_MaxLife) parentObject->GetComponent<DeletionComponent>()->SetCanDelete(true);
	m_XPos += m_XSpeed*deltaTime;
	m_YPos += m_YSpeed*deltaTime;

	if (parentObject->GetComponent<CollisionComponent>())
	{
		parentObject->GetComponent<CollisionComponent>()->SetPosition(
			m_XPos,
			m_YPos
		);
	}

	if (parentObject->GetComponent<dae::RenderComponent>())
	{
		parentObject->GetComponent<dae::RenderComponent>()->SetPosition(
			m_XPos - parentObject->GetComponent<dae::RenderComponent>()->GetWidth()/2,
			m_YPos - parentObject->GetComponent<dae::RenderComponent>()->GetHeight()/2
		);
	}

}

void BulletComponent::Render() const
{
}

bool BulletComponent::CanBounce() const
{
	if(m_Bounces <= m_MaxBounces) return true;
	return false;
}

void BulletComponent::BounceY()
{
	m_XSpeed = -m_XSpeed;
	++m_Bounces;
}

void BulletComponent::BounceX()
{
	m_YSpeed = -m_YSpeed;
	++m_Bounces;
}

void BulletComponent::BounceLeft()
{
	m_XPos -= m_XSpeed * m_DeltaTime;
	m_XSpeed = -m_XSpeed;
	++m_Bounces;
}

void BulletComponent::BounceRight()
{
	m_XPos += m_XSpeed * m_DeltaTime;
	m_XSpeed = -m_XSpeed;
	++m_Bounces;
}

void BulletComponent::BounceUp()
{
	m_YPos += m_YSpeed * m_DeltaTime;
	m_YSpeed = -m_YSpeed;
	++m_Bounces;
}

void BulletComponent::BounceDown()
{
	m_YPos -= m_YSpeed * m_DeltaTime;
	m_YSpeed = -m_YSpeed;
	++m_Bounces;
}

void BulletComponent::Initialize(float originX, float originY, float targetX, float targetY, float xspeed, float yspeed, bool isPlayerBullet)
{
	m_IsPlayerBullet = isPlayerBullet;
	m_XPos = originX;
	m_YPos = originY;

	float distance = sqrt((targetX - originX) * (targetX - originX) + (targetY - originY) * (targetY - originY));

	m_XSpeed = (targetX - originX) / distance * xspeed;
	m_YSpeed = (targetY - originY) / distance * yspeed;
}

float BulletComponent::GetX() const
{
	return m_XPos;
}

float BulletComponent::GetY() const
{
	return m_YPos;
}

bool BulletComponent::GetIsPlayerBullet() const
{
	return m_IsPlayerBullet;
}

void BulletComponent::SetX(float x)
{
	m_XPos = x;
}

void BulletComponent::SetY(float y)
{
	m_YPos = y;
}
