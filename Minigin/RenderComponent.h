#pragma once
#include "Texture2D.h"
#include "Component.h"

namespace dae {
	class RenderComponent final : public Component
	{
	public:
		RenderComponent();
		~RenderComponent() = default;

		void SetTexture(std::shared_ptr<Texture2D> newTexture);
		void Render() const override;
		void SetPosition(float x, float y);
	private:
		Texture2D* m_Texture = nullptr;
		std::shared_ptr<Texture2D> m_pTexture;
		float m_X;
		float m_Y;
	};
}