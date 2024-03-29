#pragma once
#include "Singleton.h"
#include <vector>
#include <string>
#include "Scene.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void DeleteScene(const std::string& name);
		bool SetScene(const std::string& name);
		Scene& GetCurrentScene();
		std::string GetCurrentSceneString();

		void Update(float deltaTime);
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_CurrentScene;
	};
}
