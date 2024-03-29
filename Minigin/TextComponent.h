#pragma once
#include "TextObject.h"
#include <string.h>
#include "Component.h"
#include "Font.h"

namespace dae
{
	class TextComponent final : public Component
	{
	public:
		TextComponent();
		~TextComponent();

		void Render() const override;
		void Update(float deltaTime, dae::GameObject* parentObject) override;
		void SetText(std::string newText);
		void SetPosition(float x, float y);
	private:
		TextObject* m_Text;
		std::shared_ptr<Font> m_Font;
	};
}
