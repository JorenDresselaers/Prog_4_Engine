#pragma once
#include "SceneObject.h"
#include "Component.h"
#include <unordered_map>
#include <typeinfo>
#include <thread>
#include <memory>

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:
		void Update(float deltaTime);
		void Render() const;

		template <typename T> std::shared_ptr<T> AddComponent();
		template <typename T> std::shared_ptr<T> GetComponent() const;
		template <typename T> void RemoveComponent();

		void SetParent(GameObject* newParent);
		GameObject* GetParent() const;

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector <std::shared_ptr<Component>> m_Components;

		GameObject* m_Parent;
		std::vector<std::shared_ptr<GameObject>> m_Children;

		size_t GetChildCount() const;
		std::shared_ptr<dae::GameObject> GetChildAt(int index) const;
		int GetChildIndex(std::shared_ptr<dae::GameObject> childToGet) const;
		void RemoveChild(int index);
		void AddChild(std::shared_ptr<dae::GameObject> newChild);
	};

	template<typename T>
	inline std::shared_ptr<T> GameObject::AddComponent()
	{
		auto newComponent = std::make_shared<T>();
		m_Components.emplace_back(newComponent);
		return newComponent;
	}
	
	template<typename T>
	inline std::shared_ptr<T>  GameObject::GetComponent() const
	{
		std::shared_ptr<T> ComponentToGet = nullptr;

		for (auto currentComponent : m_Components)
		{
			std::shared_ptr<T> castedComponent{ std::dynamic_pointer_cast<T>(currentComponent) };
			if (castedComponent) ComponentToGet = castedComponent;
		}

		return ComponentToGet;
	}
	
	template<typename T>
	inline void GameObject::RemoveComponent()
	{
		std::shared_ptr<T> componentToRemove = nullptr;

		for (auto currentComponent : m_Components)
		{
			std::shared_ptr<T> castedComponent{ std::dynamic_pointer_cast<T>(currentComponent) };
			if (castedComponent) componentToRemove = castedComponent;
		}

		m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), componentToRemove));
		delete componentToRemove;
	}
}
