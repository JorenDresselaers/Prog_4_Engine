#pragma once
#include <string>

class Component
{
public:
	Component();
	virtual ~Component();

	virtual void Update(float deltaTime);
	virtual void Render() const;
	virtual std::string GetName() const;

protected:
	std::string m_Name;
};

