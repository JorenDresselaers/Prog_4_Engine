#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "ResourceManager.h"
#include "BulletComponent.h"
#include "GameObject.h"
#include "SceneManager.h"

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
        if (m_MouseX && m_MouseY)
        {
            auto newBullet = std::make_shared<dae::GameObject>();
            newBullet->AddComponent<BulletComponent>()->Initialize(float(m_MouseX), float(m_MouseY), 100, 10);

            dae::SceneManager::GetInstance().GetCurrentScene().Add(newBullet);
        }
        else
        {
            std::cout << "\nMouse position not found";
        }
    }

}

void PlayerComponent::SetKeys()
{
    m_KeyUp = SDLK_UP;
    m_KeyDown = SDLK_DOWN;
    m_KeyLeft = SDLK_LEFT;
    m_KeyRight = SDLK_RIGHT;
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
