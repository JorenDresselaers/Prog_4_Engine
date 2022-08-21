#include "CollisionComponent.h"
#include "GameObject.h"
#include "DeletionComponent.h"
#include "BulletComponent.h"
#include "PlayerComponent.h"
#include "EnemyComponent.h"
#include <iostream>

CollisionComponent::CollisionComponent()
	: m_CollisionType{ CollisionType::Null }
	, m_X{ 0 }
	, m_Y{ 0 }
	, m_Width{ 0 }
	, m_Height{ 0 }
	, m_CollisionRange{ 100 }
	, m_ParentObject{ nullptr }
{
}

void CollisionComponent::Update(float deltaTime, dae::GameObject* parentObject)
{
	(void)deltaTime;
	m_ParentObject = parentObject;
}

void CollisionComponent::SetPosition(float x, float y)
{
	m_X = x;
	m_Y = y;
}

//Should probably just call a function in both colliding components, instead of hardcoding stuff here
void CollisionComponent::Collide(std::shared_ptr<CollisionComponent> other, const CollisionSide& sideX, const CollisionSide& sideY)
{
	switch (m_CollisionType)
	{
	case CollisionType::Null:
		break;
	case CollisionType::Wall:
		break;
	case CollisionType::Bullet:
		switch (other->m_CollisionType)
		{
		case CollisionType::Wall:
			//std::cout << "\nBullet bouncing wall";

			if (m_ParentObject->GetComponent<BulletComponent>()->CanBounce())
			{
				if (sideY != CollisionSide::Null)
				{
					switch (sideX)
					{
					case CollisionSide::Right:
						//m_ParentObject->GetComponent<BulletComponent>()->SetX(other->m_X + other->m_Width);
						m_ParentObject->GetComponent<BulletComponent>()->BounceY();
						break;
					case CollisionSide::Left:
						//m_ParentObject->GetComponent<BulletComponent>()->SetX(other->m_X);
						m_ParentObject->GetComponent<BulletComponent>()->BounceY();
						break;
					}
					switch (sideY)
					{
					case CollisionSide::Up:
						//m_ParentObject->GetComponent<BulletComponent>()->SetY(other->m_Y);
						m_ParentObject->GetComponent<BulletComponent>()->BounceX();
						break;
					case CollisionSide::Down:
						//m_ParentObject->GetComponent<BulletComponent>()->SetY(other->m_Y + other->m_Height);
						m_ParentObject->GetComponent<BulletComponent>()->BounceX();
						break;
					default:
						break;
					}
				}
				else
				{
					switch (sideX)
					{
					case CollisionSide::Right:
					case CollisionSide::Left:
						//std::cout << "\nBullet bouncing Y";
						m_ParentObject->GetComponent<BulletComponent>()->BounceY();
						break;
					case CollisionSide::Up:
					case CollisionSide::Down:
						//std::cout << "\nBullet bouncing X";
						m_ParentObject->GetComponent<BulletComponent>()->BounceX();
						break;
					default:
						//std::cout << "\nBullet didn't bounce";
						break;
					}
				}
			}
			else
			{
				m_ParentObject->GetComponent<DeletionComponent>()->SetCanDelete(true);
			}
			break;
		case CollisionType::EnemyTank:
			if (m_ParentObject->GetComponent<BulletComponent>()->GetIsPlayerBullet())
			{
				other->m_ParentObject->GetComponent<EnemyComponent>()->GetHit();
				m_ParentObject->GetComponent<DeletionComponent>()->SetCanDelete(true);
			}
			break;
		case CollisionType::PlayerTank:
			if (!m_ParentObject->GetComponent<BulletComponent>()->GetIsPlayerBullet())
			{
				other->m_ParentObject->GetComponent<PlayerComponent>()->GetHit();
				m_ParentObject->GetComponent<DeletionComponent>()->SetCanDelete(true);
			}
			break;
		default:
			break;
		}
		
		break;
	case CollisionType::PlayerTank:
		switch (other->m_CollisionType)
		{
		case CollisionType::Wall:
			switch (sideX)
			{
			case CollisionSide::Right:
				//std::cout << "\nTank colliding right";
				m_ParentObject->GetComponent<PlayerComponent>()->CollideRight();
				break;
			case CollisionSide::Left:
				//std::cout << "\nTank colliding left";
				m_ParentObject->GetComponent<PlayerComponent>()->CollideLeft();
				break;
			}
			switch (sideY)
			{
			case CollisionSide::Up:
				//std::cout << "\nTank colliding up";
				m_ParentObject->GetComponent<PlayerComponent>()->CollideUp();
				break;
			case CollisionSide::Down:
				//std::cout << "\nTank colliding down";
				m_ParentObject->GetComponent<PlayerComponent>()->CollideDown();
				break;
			case CollisionSide::Null:
				break;
			default:
				break;
			}
			break;
		case CollisionType::Bullet:
			break;
		case CollisionType::PlayerTank:
			break;
		case CollisionType::EnemyTank:
			break;
		case CollisionType::Crystal:
			m_ParentObject->GetComponent<PlayerComponent>()->SetPosition(
				float((rand() % 28 + 1) * 20), 
				float((rand() % 26 + 1) * 20)
			);
			break;
		default:
			break;
		}
		break;
	case CollisionType::EnemyTank:
		break;
	case CollisionType::Crystal:
		break;
	default:
		break;
	}
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

bool CollisionComponent::isColliding(std::shared_ptr<CollisionComponent> other, CollisionSide& sideX, CollisionSide& sideY)
{
	bool colliding = false;

	if (other->m_X + other->m_Width > m_X &&
		other->m_X < m_X + m_Width &&
		other->m_Y + other->m_Height > m_Y &&
		other->m_Y < m_Y + m_Height)
	{
		colliding = true;
		//side = CollisionSide::Up;

		if (other->m_X >= m_X &&
			other->m_X <= m_X + m_Width &&
			other->m_Y + other->m_Height >= m_Y &&
			other->m_Y <= m_Y + m_Height) 
		{
			//std::cout << "\nColliding right";
			sideX = CollisionSide::Right;
		}
		
		else if (other->m_X + other->m_Width >= m_X &&
			other->m_X + other->m_Width <= m_X + m_Width &&
			other->m_Y + other->m_Height >= m_Y &&
			other->m_Y <= m_Y + m_Height) 
		{
			//std::cout << "\nColliding left";
			sideX = CollisionSide::Left;
		}
		
		if (other->m_X + other->m_Width >= m_X &&
			other->m_X <= m_X + m_Width &&
			other->m_Y + other->m_Height >= m_Y &&
			other->m_Y + other->m_Height <= m_Y + m_Height) 
		{
			//std::cout << "\nColliding down";
			sideY = CollisionSide::Down;
		}
		
		else if (other->m_X + other->m_Width >= m_X &&
			other->m_X <= m_X + m_Width &&
			other->m_Y >= m_Y &&
			other->m_Y <= m_Y + m_Height) 
		{
			//std::cout << "\nColliding up";
			sideY = CollisionSide::Up;
		}
	}

	return colliding;
}

bool CollisionComponent::isColliding(std::shared_ptr<CollisionComponent> other, CollisionSide& side)
{
	bool colliding = false;

	if (other->m_X + other->m_Width > m_X &&
		other->m_X < m_X + m_Width &&
		other->m_Y + other->m_Height > m_Y &&
		other->m_Y < m_Y + m_Height)
	{
		colliding = true;
		//side = CollisionSide::Up;

		if (other->m_X >= m_X &&
			other->m_X <= m_X + m_Width &&
			other->m_Y + other->m_Height >= m_Y &&
			other->m_Y <= m_Y + m_Height)
		{
			//std::cout << "\nColliding right";
			side = CollisionSide::Right;
		}

		else if (other->m_X + other->m_Width >= m_X &&
			other->m_X + other->m_Width <= m_X + m_Width &&
			other->m_Y + other->m_Height >= m_Y &&
			other->m_Y <= m_Y + m_Height)
		{
			//std::cout << "\nColliding left";
			side = CollisionSide::Left;
		}

		if (other->m_X + other->m_Width >= m_X &&
			other->m_X <= m_X + m_Width &&
			other->m_Y + other->m_Height >= m_Y &&
			other->m_Y + other->m_Height <= m_Y + m_Height)
		{
			//std::cout << "\nColliding down";
			side = CollisionSide::Down;
		}

		else if (other->m_X + other->m_Width >= m_X &&
			other->m_X <= m_X + m_Width &&
			other->m_Y >= m_Y &&
			other->m_Y <= m_Y + m_Height)
		{
			//std::cout << "\nColliding up";
			side = CollisionSide::Up;
		}
	}

	return colliding;
}

CollisionType CollisionComponent::GetType() const
{
	return m_CollisionType;
}

void CollisionComponent::SetType(CollisionType newType)
{
	m_CollisionType = newType;
}

float CollisionComponent::GetX()
{
	return m_X;
}

float CollisionComponent::GetY()
{
	return m_Y;
}
