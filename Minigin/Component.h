#pragma once
#include <string>

namespace dae
{
	class GameObject;
}

class Component
{
public:
	Component();
	virtual ~Component();
	virtual void Update(float deltaTime, dae::GameObject* parentObject);
	virtual void Render() const;

protected:
	std::string m_Name;
};