#include "MiniginPCH.h"
#include "LivesComponent.h"

namespace dae
{
	LivesComponent::LivesComponent()
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
}