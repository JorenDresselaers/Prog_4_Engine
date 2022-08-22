#include "MiniginPCH.h"
#include "Component.h"
#include "GameObject.h"

Component::Component()
{
}

Component::~Component()
{
}

void Component::Update(float deltaTime, dae::GameObject* parentObject)
{
	(void)deltaTime; //variable unused
	(void)parentObject;
}

//void Component::Update(float deltaTime)
//{
//	(void)deltaTime; //variable unused
//}

void Component::Render() const
{
}
