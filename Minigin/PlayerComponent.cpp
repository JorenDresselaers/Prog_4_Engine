#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "ResourceManager.h"

PlayerComponent::PlayerComponent()
	: m_XPos{ 0 }
	, m_YPos{ 0 }
	, m_MovementSpeed{ 5 }
{
	m_RenderComponent = new dae::RenderComponent{};
	m_RenderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Pepper_PH.png"));
}

PlayerComponent::~PlayerComponent()
{
	delete m_RenderComponent;
}

void PlayerComponent::Update(float deltaTime)
{
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
