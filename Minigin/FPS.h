#pragma once
#include "TextComponent.h"
#include <string.h>
#include "Component.h"
#include "Font.h"

namespace dae
{
	class FPS : public Component
	{
	public:
		FPS();
		~FPS();

		void Render() const override;
		void Update(float deltaTime, dae::GameObject* parentObject) override;
		//void SetText(std::string newText);
		void SetPosition(float x, float y);
	private:
		TextComponent* m_Text;
		int m_Frames;
		float m_TimePassed;
	};
}
