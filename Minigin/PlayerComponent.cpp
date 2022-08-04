#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "ResourceManager.h"
#include "BulletComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "WallComponent.h"
#include "CollisionComponent.h"

PlayerComponent::PlayerComponent()
	: m_XPos{ 0 }
	, m_YPos{ 0 }
	, m_MovementSpeed{ 5 }
    , MovingLeft{false}
    , MovingRight{false}
    , MovingUp{false}
    , MovingDown{false}
    , m_MouseX{}
    , m_MouseY{}
{
	m_RenderComponent = new dae::RenderComponent{};
	m_RenderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Tank.png"));
    SetKeys();
}

PlayerComponent::~PlayerComponent()
{
	delete m_RenderComponent;
}

void PlayerComponent::Update(float deltaTime)
{
    if (MovingLeft) MoveLeft();
    if (MovingRight) MoveRight();
    if (MovingDown) MoveDown();
    if (MovingUp) MoveUp();

    SDL_GetMouseState(&m_MouseX, &m_MouseY);

	m_RenderComponent->SetPosition(m_XPos, m_YPos);
	m_RenderComponent->Update(deltaTime);
}

void PlayerComponent::Render() const
{
	m_RenderComponent->Render();
}

std::string PlayerComponent::GetName() const
{
	return "PlayerComponent";
}

void PlayerComponent::ProcessInput(SDL_Event e)
{
    if (e.type == SDL_KEYDOWN)
    {
        auto keyPressed = e.key.keysym.sym;
        if (keyPressed == m_KeyLeft)
        {
            MovingLeft = true;
        }
        else if (keyPressed == m_KeyRight)
        {
            MovingRight = true;
        }
        else if (keyPressed == m_KeyUp)
        {
            MovingUp = true;
        }
        else if (keyPressed == m_KeyDown)
        {
            MovingDown = true;
        }
    }

    if (e.type == SDL_KEYUP)
    {
        auto keyPressed = e.key.keysym.sym;
        if (keyPressed == m_KeyLeft)
        {
            MovingLeft = false;
        }
        else if (keyPressed == m_KeyRight)
        {
            MovingRight = false;
        }
        else if (keyPressed == m_KeyUp)
        {
            MovingUp = false;
        }
        else if (keyPressed == m_KeyDown)
        {
            MovingDown = false;
        }
    }

    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        switch (e.button.button)
        {
        case SDL_BUTTON_LEFT:
            if (m_MouseX && m_MouseY)
            {
                auto newBullet = std::make_shared<dae::GameObject>();

                auto image = dae::ResourceManager::GetInstance().LoadTexture("bullet.png");

                newBullet->AddComponent<BulletComponent>()->Initialize(m_XPos, m_YPos, float(m_MouseX), float(m_MouseY), 100, 100);
                newBullet->AddComponent<dae::RenderComponent>()->SetTexture(image);

                newBullet->AddComponent<CollisionComponent>()->Initialize(
                    m_XPos + float(m_RenderComponent->GetWidth() / 2),
                    m_YPos - float(m_RenderComponent->GetHeight() / 2),
                    newBullet->GetComponent<dae::RenderComponent>()->GetWidth(),
                    newBullet->GetComponent<dae::RenderComponent>()->GetHeight()
                );

                dae::SceneManager::GetInstance().GetCurrentScene().Add(newBullet);
            }
            else
            {
                std::cout << "\nMouse position not found";
            }
            break;
        case SDL_BUTTON_RIGHT:
            if (m_MouseX && m_MouseY)
            {
                auto newWall= std::make_shared<dae::GameObject>();

                auto image = dae::ResourceManager::GetInstance().LoadTexture("wall.png");

                newWall->AddComponent<dae::RenderComponent>()->SetTexture(image);
                newWall->AddComponent<dae::RenderComponent>()->SetPosition(m_MouseX - float(m_RenderComponent->GetWidth() / 2), m_MouseY - float(m_RenderComponent->GetHeight() / 2));
                //newWall->AddComponent<WallComponent>()->Initialize(m_MouseX - float(m_RenderComponent->GetWidth() / 2), m_MouseY - float(m_RenderComponent->GetHeight() / 2));
                newWall->AddComponent<CollisionComponent>()->Initialize(
                    m_MouseX - float(m_RenderComponent->GetWidth() / 2),
                    m_MouseY - float(m_RenderComponent->GetHeight() / 2),
                    newWall->GetComponent<dae::RenderComponent>()->GetWidth(),
                    newWall->GetComponent<dae::RenderComponent>()->GetHeight()
                );

                dae::SceneManager::GetInstance().GetCurrentScene().Add(newWall);
            }
            else
            {
                std::cout << "\nMouse position not found";
            }
            break;
        }
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

void PlayerComponent::MoveLeft()
{
	m_XPos -= m_MovementSpeed;
}

void PlayerComponent::MoveRight()
{
	m_XPos += m_MovementSpeed;
}

void PlayerComponent::MoveUp()
{
	m_YPos -= m_MovementSpeed;
}

void PlayerComponent::MoveDown()
{
	m_YPos += m_MovementSpeed;
}
