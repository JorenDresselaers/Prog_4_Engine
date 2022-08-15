#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "SDL.h"

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

	int width{};
	int height{};
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &width, &height);
	m_Width = float(width);
	m_Height = float(height);

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
	//std::cout << "\nNew position: " << x << ", " << y;
	m_X = x;
	m_Y = y;
}

std::shared_ptr<dae::Texture2D> dae::RenderComponent::GetTexture() const
{
	return m_pTexture;
}

float dae::RenderComponent::GetWidth() const
{
	return m_Width;
}

float dae::RenderComponent::GetHeight() const
{
	return m_Height;
}
