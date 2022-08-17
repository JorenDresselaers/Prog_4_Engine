#include "EnemyComponent.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "DeletionComponent.h"

EnemyComponent::EnemyComponent()
    : m_XPos{ 0 }
    , m_YPos{ 0 }
    , m_Lives{ 1 }
{
}

void EnemyComponent::Update(float deltaTime, dae::GameObject* parentObject)
{
    (void)deltaTime;

    if (parentObject->GetComponent<CollisionComponent>())
    {
        parentObject->GetComponent<CollisionComponent>()->SetPosition(
            m_XPos,
            m_YPos
        );
    }

    if (parentObject->GetComponent<dae::RenderComponent>())
    {
        parentObject->GetComponent<dae::RenderComponent>()->SetPosition(m_XPos, m_YPos);
    }

    if (m_Lives <= 0)
    {
        parentObject->GetComponent<DeletionComponent>()->SetCanDelete(true);
    }
}

void EnemyComponent::Initialize(float x, float y, int lives)
{
    m_XPos = x;
    m_YPos = y;
    m_Lives = lives;
}

void EnemyComponent::GetHit()
{
    --m_Lives;
}
