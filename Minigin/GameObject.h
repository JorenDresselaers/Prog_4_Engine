#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "Component.h"
#include <unordered_map>
#include <typeinfo>
#include "RenderComponent.h"

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:
		void Update(/*float deltaTime */);
		void Render() const;

		//void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		template <typename T> std::shared_ptr<T> AddComponent();
		template <typename T> T* GetComponent() const;
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
		Transform m_Transform;
		// todo: mmm, every gameobject has a texture? Is that correct?
		//std::shared_ptr<Texture2D> m_Texture{};
		std::vector <std::shared_ptr<Component>> m_Components;
		//std::unordered_map < std::string, std::shared_ptr<Component*>> m_Components;

		GameObject* m_Parent;
		std::vector<std::shared_ptr<GameObject>> m_Children;

		size_t GetChildCount() const;
		std::shared_ptr<dae::GameObject> GetChildAt(int index) const;
		void RemoveChild(int index);
		void AddChild(std::shared_ptr<dae::GameObject> newChild);
	};

	template<typename T>
	inline std::shared_ptr<T> GameObject::AddComponent()
	{
		auto newComponent = std::make_shared<T>();
		m_Components.emplace_back(newComponent);
		return newComponent;

		//auto test = std::make_shared<RenderComponent>

		//
		//T* componentToReturn = nullptr;
		//componentToReturn = newComponent.get();
		//
		//return componentToReturn;

		//auto newComponent = std::make_shared<T>;
		//m_Components.insert("Component", newComponent);
	}
	
	template<typename T>
	inline T* GameObject::GetComponent() const
	{
		T* ComponentToGet = nullptr;
		//for (int i{ 0 }; i < m_Components.size(); ++i)
		//{
		//	if (typeid(m_Components.at(i)) == typeid(ComponentToGet))
		//	{ 
		//		ComponentToGet = m_Components.at(i);
		//	}
		//}
		//return dynamic_cast<T*>(ComponentToGet.get());
		//return dynamic_cast<T*>(m_Components.at(0).get());


		for (int i{ 0 }; i < m_Components.size(); ++i)
		{
			if (typeid(m_Components.at(i).get()) == typeid(ComponentToGet))
			{ 
				//ComponentToGet = dynamic_cast<T*>(m_Components.at(i).get());
			}
		}


		return ComponentToGet;
	}
	
	template<typename T>
	inline void GameObject::RemoveComponent()
	{
		//T* ComponentToRemove = nullptr;
		//for (int i{ 0 }; i < m_Components.size(); ++i)
		//{
		//	if (typeid(m_Components.at(i).get()) == typeid(ComponentToRemove))
		//	{
		//		delete m_Components.at(i);
		//		std::erase(m_Components.at(i));
		//		break;
		//	}
		//}
	}
}
