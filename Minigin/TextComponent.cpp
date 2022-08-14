#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Font.h"
#include "ResourceManager.h"

dae::TextComponent::TextComponent()
{
	if (!m_Font) m_Font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	m_Text = new TextObject("ERROR", m_Font);
}

dae::TextComponent::~TextComponent()
{
	delete m_Text;
}

void dae::TextComponent::Render() const
{
	m_Text->Render();
}

void dae::TextComponent::Update(float deltaTime, dae::GameObject* parentObject)
{
	(void)parentObject;
	m_Text->Update(deltaTime, parentObject);
}

void dae::TextComponent::SetText(std::string newText)
{
	m_Text->SetText(newText);
}

void dae::TextComponent::SetPosition(float x, float y)
{
	m_Text->SetPosition(x, y);
}
