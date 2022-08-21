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
#include <string>
#include "ScoreManager.h"

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
    , m_TotalScore{ 0 }
    , m_Lives{ 3 }
    , m_HasDied{ false }
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
	//parentObject->GetComponent<dae::TextComponent>()->SetPosition(m_XPos, m_YPos-20);
	parentObject->GetComponent<dae::TextComponent>()->SetText("Score: " + std::to_string(ScoreManager::GetInstance().GetScore()));
}

void PlayerComponent::Render() const
{
	//m_RenderComponent->Render();
}

std::string PlayerComponent::GetName() const
{
	return "PlayerComponent";
}

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
    else if (e.keysym.sym == 'q')
    {
        GetHit();
    }
    else if (e.keysym.sym == 'h')
    {
        ScoreManager::GetInstance().AddScore(500);
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
                200,
                200,
                true
            );
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
            //dae::AudioManager::GetInstance().Play("Fishfight.mp3", 1);
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

void PlayerComponent::MoveLeft()
{
	m_XPos -= m_MovementSpeed * m_DeltaTime;
}

void PlayerComponent::MoveRight()
{
	m_XPos += m_MovementSpeed * m_DeltaTime;
}

void PlayerComponent::MoveUp()
{
	m_YPos -= m_MovementSpeed * m_DeltaTime;
}

void PlayerComponent::MoveDown()
{
	m_YPos += m_MovementSpeed * m_DeltaTime;
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

void PlayerComponent::GetHit()
{
    --m_Lives;
    SetHasDied(true);
}

void PlayerComponent::SetLives(int newLives)
{
    m_Lives = newLives;
}

int PlayerComponent::GetLives()
{
    return m_Lives;
}

void PlayerComponent::SetHasDied(bool b)
{
    m_HasDied = b;
}

bool PlayerComponent::GetHasDied()
{
    return m_HasDied;
}

void PlayerComponent::AddScore(int score)
{
    m_TotalScore += score;
    m_ParentObject->GetComponent<dae::TextComponent>()->SetText("Score:" + m_TotalScore);
}

int PlayerComponent::GetScore()
{
    return m_TotalScore;
}
