#include "EnemyComponent.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "DeletionComponent.h"
#include "ScoreManager.h"
#include "ScoreComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "BulletComponent.h"

#include <iostream>

EnemyComponent::EnemyComponent()
    : m_XPos{ 0 }
    , m_YPos{ 0 }
    , m_Lives{ 1 }
    , m_ParentObject{ nullptr }
    , m_ShotCooldown{1}
    , m_CurrentCooldown{0}
{
    m_CurrentCooldown = float(rand() % int(m_ShotCooldown));
}

void EnemyComponent::Update(float deltaTime, dae::GameObject* parentObject)
{
    m_ParentObject = parentObject;

    m_CurrentCooldown += deltaTime;
    if (m_CurrentCooldown >= m_ShotCooldown)
    {
        Shoot();
    }

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

void EnemyComponent::Shoot()
{
    int shotDirection = rand() % 4;
    //std::cout << "\n"  << shotDirection;
    float shotXPos{ 0 }, shotYPos{ 0 };
    switch (shotDirection)
    {
    case 1:
        shotXPos = 10;
        break;
    case 2:
        shotYPos = 10;
        break;
    case 3:
        shotXPos = -10;
        break;
    case 4:
        shotYPos = -10;
        break;
    }

    m_CurrentCooldown = 0;
    auto newBullet = std::make_shared<dae::GameObject>();

    auto image = dae::ResourceManager::GetInstance().LoadTexture("bullet.png");

    newBullet->AddComponent<BulletComponent>()->Initialize(
        m_XPos + m_ParentObject->GetComponent<dae::RenderComponent>()->GetWidth() / 2,
        m_YPos + m_ParentObject->GetComponent<dae::RenderComponent>()->GetHeight() / 2,
        m_XPos + m_ParentObject->GetComponent<dae::RenderComponent>()->GetWidth() / 2 + shotXPos,
        m_YPos + m_ParentObject->GetComponent<dae::RenderComponent>()->GetHeight() / 2 + shotYPos,
        200,
        200);
    newBullet->AddComponent<dae::RenderComponent>()->SetTexture(image);

    newBullet->AddComponent<CollisionComponent>()->Initialize(
        0,
        0,
        1,
        1,
        CollisionType::Bullet
    );

    newBullet->AddComponent<DeletionComponent>();

    dae::SceneManager::GetInstance().GetCurrentScene().Add(newBullet);
}
