#include "FPS.h"
#include <string>
#include <iostream>

dae::FPS::FPS()
	: m_Text{ nullptr }
	, m_Frames{ 0 }
	, m_TimePassed{ 0 }
{
	m_Text = new TextComponent();
	m_Text->SetText("69 FPS");
}

dae::FPS::~FPS()
{
	delete m_Text;
}

void dae::FPS::Render() const
{
	m_Text->Render();
}

void dae::FPS::Update(float deltaTime, dae::GameObject* parentObject)
{
	(void)parentObject;

	++m_Frames;
	m_TimePassed += deltaTime;
	//m_Text->SetText("Toodles");

	if (m_TimePassed >= 1.f)
	{
		std::string framesPerSecond{ std::to_string(m_Frames) + " FPS"};
		m_Text->SetText(framesPerSecond);
		std::cout << "\nOutput: " << framesPerSecond;
		m_TimePassed = 0;
		m_Frames = 0;
	}

	m_Text->Update(deltaTime, nullptr);
}

void dae::FPS::SetPosition(float x, float y)
{
	m_Text->SetPosition(x, y);
}
