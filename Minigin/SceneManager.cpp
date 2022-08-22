#include "MiniginPCH.h"

#include "Scene.h"
#include "SceneManager.h"

using namespace dae;

void SceneManager::Update(float deltaTime)
{
	if(m_CurrentScene) m_CurrentScene->Update(deltaTime);
}

void SceneManager::Render()
{
	if (m_CurrentScene) m_CurrentScene->Render();
}

dae::Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	m_CurrentScene = scene;
	return *scene;
}

void dae::SceneManager::DeleteScene(const std::string& name)
{
	for (size_t currentScene{ 0 }; currentScene < m_Scenes.size(); ++currentScene)
	{
		if (m_Scenes.at(currentScene)->m_Name == name)
		{
			m_Scenes.erase(std::remove(m_Scenes.begin(), m_Scenes.end(), m_Scenes.at(currentScene)), m_Scenes.end());
		}
	}
}

bool dae::SceneManager::SetScene(const std::string& name)
{
	for (auto currentScene : m_Scenes)
	{
		if (currentScene->m_Name == name)
		{
			m_CurrentScene = currentScene;
			return true;
		}
	}
	return false;
}

dae::Scene& dae::SceneManager::GetCurrentScene()
{
	return *m_CurrentScene;
}

std::string dae::SceneManager::GetCurrentSceneString()
{
	return m_CurrentScene->GetName();
}
