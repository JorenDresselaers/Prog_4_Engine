#pragma once
#include "Texture2D.h"
#include "Component.h"
#include <memory>

namespace dae {
	class RenderComponent final : public Component
	{
	public:
		RenderComponent();
		~RenderComponent() = default;

		void SetTexture(std::shared_ptr<Texture2D> newTexture);
		void Render() const override;
		void SetPosition(float x, float y);
		void SetDimensions(float width, float height);

		std::shared_ptr<Texture2D> GetTexture() const;
		float GetWidth() const;
		float GetHeight() const;

	private:
		Texture2D* m_Texture = nullptr;
		std::shared_ptr<Texture2D> m_pTexture;
		float m_X;
		float m_Y;
		float m_Width;
		float m_Height;
	};
}