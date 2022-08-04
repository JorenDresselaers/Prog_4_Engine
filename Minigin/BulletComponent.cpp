#include "MiniginPCH.h"
#include "BulletComponent.h"
#include "ResourceManager.h"

BulletComponent::BulletComponent()
	: m_XPos{ 0 }
	, m_YPos{ 0 }
	, m_XSpeed{ 0 }
	, m_YSpeed{ 0 }
	, m_Bounces{ 0 }
	, m_MaxBounces{ 5 }
{
	//m_RenderComponent = new dae::RenderComponent();

	//auto image = dae::ResourceManager::GetInstance().LoadTexture("wall.png");
	//m_RenderComponent->SetTexture(image);
}

BulletComponent::~BulletComponent()
{
	//delete m_RenderComponent;
	//m_RenderComponent = nullptr;
}

void BulletComponent::Update(float deltaTime)
{
	m_XPos += m_XSpeed*deltaTime;
	m_YPos += m_YSpeed*deltaTime;

	//m_RenderComponent->SetPosition(m_XPos, m_YPos);
}

void BulletComponent::Render() const
{
	//m_RenderComponent->Render();
}

void BulletComponent::Initialize(float originX, float originY, float targetX, float targetY, float xspeed, float yspeed)
{
	//int width{};
	//int height{};
	//SDL_QueryTexture(m_RenderComponent->GetTexture()->GetSDLTexture(), nullptr, nullptr, &width, &height);

	m_XPos = originX;
	m_YPos = originY;
	//m_XPos = originX - m_RenderComponent->GetWidth() / 2;
	//m_YPos = originY - m_RenderComponent->GetHeight() / 2;

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
