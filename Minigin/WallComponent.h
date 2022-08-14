#pragma once
#include "Component.h"
#include "RenderComponent.h"

//OBSOLETE

class WallComponent : public Component
{
public:
	WallComponent();
	~WallComponent();

	void Update(float deltaTime, dae::GameObject* parentObject) override;
	void Render() const override;

	void Initialize(float xPos, float yPos);
	void Initialize(float xPos, float yPos, std::string imagePath);

private:
	dae::RenderComponent* m_RenderComponent;
};

