#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "Component.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		void Update(/*float deltaTime */); // this would have float deltaTime
										   // but I didn't get it done on time
		void Render() const;

		//void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		//template <typename T> void AddComponent(T*);
		//template <typename T> T* GetComponent() const;
		//template <typename T> void RemoveComponent();

		void SetParent(GameObject* parent);
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

		GameObject* m_Parent;
		std::vector<std::shared_ptr<GameObject>> m_Children;

		size_t GetChildCount() const;
		std::shared_ptr<dae::GameObject> GetChildAt(int index) const;
		void RemoveChild(int index);
		void AddChild(std::shared_ptr<dae::GameObject> go);
	};

	//template<typename T>
	//inline void GameObject::AddComponent(T*)
	//{
	//	m_Components.push_back(Component(T*));
	//}
	//
	//template<typename T>
	//inline T* GameObject::GetComponent() const
	//{
	//	return nullptr;
	//}
	//
	//template<typename T>
	//inline void GameObject::RemoveComponent()
	//{
	//}
}
