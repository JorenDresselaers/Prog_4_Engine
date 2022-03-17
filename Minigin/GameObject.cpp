#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"


void dae::GameObject::SetParent(GameObject* parent)
{
	m_Parent = parent;
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

void dae::GameObject::Update(/*float deltaTime */)
{
}

void dae::GameObject::Render() const
{
	//const auto& pos = m_Transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
//}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

size_t dae::GameObject::GetChildCount() const
{
	return m_Children.size();
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAt(int index) const
{
	return m_Children.at(index);
}

void dae::GameObject::RemoveChild(int index)
{
	m_Children.erase(m_Children.begin() + index-1);
}

void dae::GameObject::AddChild(std::shared_ptr<dae::GameObject> go)
{
	m_Children.push_back(go);
}