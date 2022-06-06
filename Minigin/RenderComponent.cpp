#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::RenderComponent::RenderComponent()
	: m_X{ 0 }
	, m_Y{ 0 }
{
	m_Name = "RenderComponent";
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> newTexture)
{
	m_Texture = newTexture.get();
	m_pTexture = newTexture;
}

void dae::RenderComponent::Render() const
{
	if (m_Texture)
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, m_X, m_Y);
	}
}

void dae::RenderComponent::SetPosition(float x, float y)
{
	m_X = x;
	m_Y = y;
}
