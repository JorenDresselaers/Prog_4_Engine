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
	m_RenderComponent = new dae::RenderComponent();

	auto image = dae::ResourceManager::GetInstance().LoadTexture("Pepper_PH.png");
	m_RenderComponent->SetTexture(image);
}

BulletComponent::~BulletComponent()
{
	delete m_RenderComponent;
	m_RenderComponent = nullptr;
}

void BulletComponent::Update(float deltaTime)
{
	m_XPos += m_XSpeed*deltaTime;
	m_YPos += m_YSpeed*deltaTime;

	m_RenderComponent->SetPosition(m_XPos, m_YPos);
}

void BulletComponent::Render() const
{
	m_RenderComponent->Render();
}

void BulletComponent::Initialize(float x, float y, float xspeed, float yspeed)
{
	m_XPos = x;
	m_YPos = y;
	m_XSpeed = xspeed;
	m_YSpeed = yspeed;
}
