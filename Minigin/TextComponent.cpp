#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Font.h"

dae::TextComponent::TextComponent()
{
}

dae::TextComponent::~TextComponent()
{
	delete m_Text;
}

void dae::TextComponent::Render() const
{
	m_Text->Render();
}

void dae::TextComponent::Update()
{
	m_Text->Update();
}

void dae::TextComponent::SetText(std::string newText)
{
	m_Text->SetText(newText);
}

void dae::TextComponent::SetPosition(float x, float y)
{
	m_Text->SetPosition(x, y);
}
