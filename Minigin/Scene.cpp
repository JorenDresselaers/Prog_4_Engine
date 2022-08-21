#include "MiniginPCH.h"
#include "Scene.h"
#include "DeletionComponent.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) 
	: m_Name(name) 
{}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update(float deltaTime)
{
	if (m_Objects.size() > 0)
	{
		for (size_t object{}; object < m_Objects.size(); ++object)
		{
			m_Objects.at(object)->Update(deltaTime);

			if (m_Objects.at(object)->GetComponent<DeletionComponent>() != nullptr)
			{
				if (m_Objects.at(object)->GetComponent<DeletionComponent>()->GetCanDelete())
				{
					m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), m_Objects.at(object)), m_Objects.end());
				}
			}
		}
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

const std::vector<std::shared_ptr<GameObject>>& dae::Scene::GetObjects() const
{
	return m_Objects;
}

std::string dae::Scene::GetName() const
{
	return m_Name;
}

