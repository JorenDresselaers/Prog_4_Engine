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
