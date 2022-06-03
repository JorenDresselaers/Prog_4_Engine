#pragma once
#include "Component.h"

namespace dae
{
	class LivesComponent : Component
	{
	public:
		LivesComponent();
		~LivesComponent() = default;

		void Update(float deltaTime) override;

		void GainLife();
		void LoseLife();
		void SetLives(int newLives);

	private:
		int m_Lives;

	};
}