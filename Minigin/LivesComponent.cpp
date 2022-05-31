#include "MiniginPCH.h"
#include "LivesComponent.h"

LivesComponent::LivesComponent(int currentLives)
	: m_Lives{ currentLives }
{
}

void LivesComponent::Update(float deltaTime)
{
	(void)deltaTime;
}

void LivesComponent::GainLife()
{
	++m_Lives;
}

void LivesComponent::LoseLife()
{
	--m_Lives;
}

void LivesComponent::SetLives(int newLives)
{
	m_Lives = newLives;
}
