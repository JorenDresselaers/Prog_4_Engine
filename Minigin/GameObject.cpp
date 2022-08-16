#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "SceneManager.h"

void dae::GameObject::SetParent(GameObject* newParent)
{
	//m_Parent->RemoveChild(0);
	m_Parent = newParent;
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_Parent;
}

dae::GameObject::GameObject()
	:m_Parent{ nullptr }
{
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime)
{
	for (auto& currentComponent : m_Components)
	{
		currentComponent->Update(deltaTime, this);

		//dae::SceneManager::GetInstance().GetCurrentScene().
	}
}

void dae::GameObject::Render() const
{
	for (auto& currentComponent : m_Components)
	{
		currentComponent->Render();
	}
}

size_t dae::GameObject::GetChildCount() const
{
	return m_Children.size();
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAt(int index) const
{
	return m_Children.at(index);
}

int dae::GameObject::GetChildIndex(std::shared_ptr<dae::GameObject> childToGet) const
{
	auto index = std::find(m_Children.begin(), m_Children.end(), childToGet);
	int indexToReturn{ -1 };

	if (index != m_Children.end())
	{
		indexToReturn = int(index - m_Children.begin());
	}

	return indexToReturn;
}

void dae::GameObject::RemoveChild(int index)
{
	m_Children.erase(m_Children.begin() + index-1);
}

void dae::GameObject::AddChild(std::shared_ptr<dae::GameObject> newChild)
{
	m_Children.push_back(newChild);
}