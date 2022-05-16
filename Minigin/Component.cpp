#include "MiniginPCH.h"
#include "Component.h"

Component::Component()
{
}

Component::~Component()
{
}

void Component::Update(/*float deltaTime */)
{
}

void Component::Render() const
{
}

std::string Component::GetName() const
{
	return m_Name;
}


