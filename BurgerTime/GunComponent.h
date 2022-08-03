#pragma once
#include "Component.h"

class GunComponent : public Component
{
public:
	GunComponent();
	~GunComponent();

	void Update(float deltaTime) override;
	void Render() const override;

	void Shoot(float x, float y);

private:
	//float m_Rotation;

};

