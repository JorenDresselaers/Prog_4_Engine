#pragma once
#include "Texture2D.h"

namespace dae {
	class RenderComponent final
	{
	public:
		void SetTexture(Texture2D* newTexture);
		void Render() const;
	private:
		Texture2D* m_Texture;
	};
}