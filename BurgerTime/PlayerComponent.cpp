#include "PlayerComponent.h"
#include "ResourceManager.h"
#include "BulletComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "DeletionComponent.h"
#include "TextComponent.h"
#include "AudioManager.h"

PlayerComponent::PlayerComponent()
	: m_XPos{ 0 }
	, m_YPos{ 0 }
	, m_MovementSpeed{ 100 }
    , MovingLeft{ false }
    , MovingRight{ false }
    , MovingUp{ false }
    , MovingDown{ false }
    , m_ParentObject{ nullptr }
    , m_MaxCooldown{ 1 }
    , m_CurrentCooldown{ m_MaxCooldown }
{
    SetKeys();
}

PlayerComponent::~PlayerComponent()
{
	//delete m_RenderComponent;
}

void PlayerComponent::Update(float deltaTime, dae::GameObject* parentObject)
{
    m_DeltaTime = deltaTime;
    m_CurrentCooldown += deltaTime;

    if(m_ParentObject == nullptr) m_ParentObject = parentObject;

    if (MovingLeft) MoveLeft(deltaTime);
    if (MovingRight) MoveRight(deltaTime);
    if (MovingDown) MoveDown(deltaTime);
    if (MovingUp) MoveUp(deltaTime);

    if (parentObject->GetComponent<CollisionComponent>())
    {
        parentObject->GetComponent<CollisionComponent>()->SetPosition(
            m_XPos,
            m_YPos
        );
    }

    //SDL_GetMouseState(&m_MouseX, &m_MouseY);

	parentObject->GetComponent<dae::RenderComponent>()->SetPosition(m_XPos, m_YPos);
	parentObject->GetComponent<dae::TextComponent>()->SetPosition(m_XPos, m_YPos-20);
}

void PlayerComponent::Render() const
{
	//m_RenderComponent->Render();
}

std::string PlayerComponent::GetName() const
{
	return "PlayerComponent";
}

/*
void PlayerComponent::ProcessInput(SDL_Event e)
{
    //if (e.type == SDL_KEYDOWN)
    //{
    //    auto keyPressed = e.key.keysym.sym;
    //    if (keyPressed == m_KeyLeft)
    //    {
    //        MovingLeft = true;
    //    }
    //    else if (keyPressed == m_KeyRight)
    //    {
    //        MovingRight = true;
    //    }
    //    else if (keyPressed == m_KeyUp)
    //    {
    //        MovingUp = true;
    //    }
    //    else if (keyPressed == m_KeyDown)
    //    {
    //        MovingDown = true;
    //    }
    //}

    //if (e.type == SDL_KEYUP)
    //{
    //    auto keyPressed = e.key.keysym.sym;
    //    if (keyPressed == m_KeyLeft)
    //    {
    //        MovingLeft = false;
    //    }
    //    else if (keyPressed == m_KeyRight)
    //    {
    //        MovingRight = false;
    //    }
    //    else if (keyPressed == m_KeyUp)
    //    {
    //        MovingUp = false;
    //    }
    //    else if (keyPressed == m_KeyDown)
    //    {
    //        MovingDown = false;
    //    }
    //}

    //if (e.type == SDL_MOUSEBUTTONDOWN)
    //{
    //    switch (e.button.button)
    //    {
    //    case SDL_BUTTON_LEFT:
    //        if (m_MouseX && m_MouseY)
    //        {
    //            auto newBullet = std::make_shared<dae::GameObject>();
    //
    //            auto image = dae::ResourceManager::GetInstance().LoadTexture("bullet.png");
    //
    //            newBullet->AddComponent<BulletComponent>()->Initialize(m_XPos, m_YPos, float(m_MouseX), float(m_MouseY), 100, 100);
    //            newBullet->AddComponent<dae::RenderComponent>()->SetTexture(image);
    //
    //            newBullet->AddComponent<CollisionComponent>()->Initialize(
    //                m_XPos + float(m_ParentObject->GetComponent<dae::RenderComponent>()->GetWidth() / 2),
    //                m_YPos - float(m_ParentObject->GetComponent<dae::RenderComponent>()->GetHeight() / 2),
    //                newBullet->GetComponent<dae::RenderComponent>()->GetWidth(),
    //                newBullet->GetComponent<dae::RenderComponent>()->GetHeight(),
    //                CollisionType::Bullet
    //            );
    //
    //            newBullet->AddComponent<DeletionComponent>();
    //
    //            dae::SceneManager::GetInstance().GetCurrentScene().Add(newBullet);
    //        }
    //        else
    //        {
    //            std::cout << "\nMouse position not found";
    //        }
    //        break;
    //    case SDL_BUTTON_RIGHT:
    //        if (m_MouseX && m_MouseY)
    //        {
    //            auto newWall= std::make_shared<dae::GameObject>();
    //
    //            auto image = dae::ResourceManager::GetInstance().LoadTexture("wall.png");
    //
    //            newWall->AddComponent<dae::RenderComponent>()->SetTexture(image);
    //            newWall->AddComponent<dae::RenderComponent>()->SetPosition(float(m_MouseX), float(m_MouseY));
    //            newWall->AddComponent<CollisionComponent>()->Initialize(
    //                float(m_MouseX),
    //                float(m_MouseY),
    //                newWall->GetComponent<dae::RenderComponent>()->GetWidth(),
    //                newWall->GetComponent<dae::RenderComponent>()->GetHeight(),
    //                CollisionType::Wall
    //            );
    //            
    //            dae::SceneManager::GetInstance().GetCurrentScene().Add(newWall);
    //        }
    //        else
    //        {
    //            std::cout << "\nMouse position not found";
    //        }
    //        break;
    //    }
    //}
}
*/

void PlayerComponent::ProcessKeyUp(const SDL_KeyboardEvent& e)
{
    if (e.keysym.sym == m_KeyLeft)
    {
        MovingLeft = false;
    }
    else if (e.keysym.sym == m_KeyRight)
    {
        MovingRight = false;
    }
    else if (e.keysym.sym == m_KeyUp)
    {
        MovingUp = false;
    }
    else if (e.keysym.sym == m_KeyDown)
    {
        MovingDown = false;
    }
}

void PlayerComponent::ProcessKeyDown(const SDL_KeyboardEvent& e)
{
    if (e.keysym.sym == m_KeyLeft)
    {
        MovingLeft = true;
    }
    else if (e.keysym.sym == m_KeyRight)
    {
        MovingRight = true;
    }
    else if (e.keysym.sym == m_KeyUp)
    {
        MovingUp = true;
    }
    else if (e.keysym.sym == m_KeyDown)
    {
        MovingDown = true;
    }
}

void PlayerComponent::ProcessMouseUp(const SDL_MouseButtonEvent& e)
{
    (void)e;
}

void PlayerComponent::ProcessMouseDown(const SDL_MouseButtonEvent& e)
{
    if (e.button == SDL_BUTTON_LEFT)
    {
        if (m_CurrentCooldown >= m_MaxCooldown)
        {
            m_CurrentCooldown = 0;
            auto newBullet = std::make_shared<dae::GameObject>();

            auto image = dae::ResourceManager::GetInstance().LoadTexture("bullet.png");

            newBullet->AddComponent<BulletComponent>()->Initialize(
                m_XPos + m_ParentObject->GetComponent<dae::RenderComponent>()->GetWidth() / 2,
                m_YPos + m_ParentObject->GetComponent<dae::RenderComponent>()->GetHeight() / 2,
                float(e.x),
                float(e.y),
                100,
                100);
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

        //dae::AudioManager::GetInstance().Play("Fishfight.wav", 1);
    }
    else if (e.button == SDL_BUTTON_RIGHT)
    {

    }
}

void PlayerComponent::SetKeys()
{
    //m_KeyUp = SDLK_UP;
    //m_KeyDown = SDLK_DOWN;
    //m_KeyLeft = SDLK_LEFT;
    //m_KeyRight = SDLK_RIGHT;
    m_KeyUp = SDLK_w;
    m_KeyDown = SDLK_s;
    m_KeyLeft = SDLK_a;
    m_KeyRight = SDLK_d;
}

void PlayerComponent::SetKeys(SDL_KeyCode up, SDL_KeyCode down, SDL_KeyCode left, SDL_KeyCode right)
{
    m_KeyUp = up;
    m_KeyDown = down;
    m_KeyLeft = left;
    m_KeyRight = right;
}

void PlayerComponent::SetPosition(float x, float y)
{
	m_XPos = x;
	m_YPos = y;
}

void PlayerComponent::MoveLeft(float deltaTime)
{
	m_XPos -= m_MovementSpeed * deltaTime;
}

void PlayerComponent::MoveRight(float deltaTime)
{
	m_XPos += m_MovementSpeed * deltaTime;
}

void PlayerComponent::MoveUp(float deltaTime)
{
	m_YPos -= m_MovementSpeed * deltaTime;
}

void PlayerComponent::MoveDown(float deltaTime)
{
	m_YPos += m_MovementSpeed * deltaTime;
}

void PlayerComponent::CollideUp()
{
    m_YPos -= m_MovementSpeed * m_DeltaTime;
}

void PlayerComponent::CollideDown()
{
    m_YPos += m_MovementSpeed * m_DeltaTime;
}

void PlayerComponent::CollideLeft()
{
    m_XPos += m_MovementSpeed * m_DeltaTime;
}

void PlayerComponent::CollideRight()
{
    m_XPos -= m_MovementSpeed * m_DeltaTime;
}
