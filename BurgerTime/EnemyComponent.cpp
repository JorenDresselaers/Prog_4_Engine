#include "EnemyComponent.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "DeletionComponent.h"
#include "ScoreManager.h"
#include "ScoreComponent.h"

#include <iostream>

EnemyComponent::EnemyComponent()
    : m_XPos{ 0 }
    , m_YPos{ 0 }
    , m_Lives{ 1 }
    , m_ParentObject{ nullptr }
{
}

void EnemyComponent::Update(float deltaTime, dae::GameObject* parentObject)
{
    (void)deltaTime;
    m_ParentObject = parentObject;

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
    if (m_Lives <= 0)
    {
        m_ParentObject->GetComponent<DeletionComponent>()->SetCanDelete(true);
        ScoreManager::GetInstance().AddScore(m_ParentObject->GetComponent<ScoreComponent>()->GetScore());
    }
}
