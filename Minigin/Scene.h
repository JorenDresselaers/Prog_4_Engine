#pragma once
#include "SceneManager.h"
#include "GameObject.h"
#include <vector>

namespace dae
{
	class SceneObject;
	class Scene final
	{
		//friend Scene& SceneManager::CreateScene(const std::string& name);
		friend class SceneManager;
	public:
		void Add(const std::shared_ptr<GameObject>& object);

		void Update(float deltaTime);
		void Render() const;

		const std::vector<std::shared_ptr<GameObject>>& GetObjects() const;
		std::string GetName() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::shared_ptr<GameObject> > m_Objects{};

		static unsigned int m_IdCounter; 
	};

}
