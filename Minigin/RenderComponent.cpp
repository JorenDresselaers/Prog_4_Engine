#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::RenderComponent::RenderComponent()
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
		Renderer::GetInstance().RenderTexture(*m_Texture, 0, 0);
	}
}
