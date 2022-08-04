#include "MiniginPCH.h"
#include "WallComponent.h"
#include "ResourceManager.h"

WallComponent::WallComponent()
{
	//m_RenderComponent = new dae::RenderComponent();

	//auto image = dae::ResourceManager::GetInstance().LoadTexture("wall.png");
	//m_RenderComponent->SetTexture(image);
}

WallComponent::~WallComponent()
{
	delete m_RenderComponent;
	m_RenderComponent = nullptr;
}

void WallComponent::Update(float deltaTime)
{
	m_RenderComponent->Update(deltaTime);
}

void WallComponent::Render() const
{
	m_RenderComponent->Render();
}

void WallComponent::Initialize(float xPos, float yPos)
{
	m_RenderComponent->SetPosition(xPos, yPos);

	auto image = dae::ResourceManager::GetInstance().LoadTexture("wall.png");
	m_RenderComponent->SetTexture(image);
}

void WallComponent::Initialize(float xPos, float yPos, std::string imagePath)
{
	m_RenderComponent->SetPosition(xPos, yPos);

	auto image = dae::ResourceManager::GetInstance().LoadTexture(imagePath);
	m_RenderComponent->SetTexture(image);
}
