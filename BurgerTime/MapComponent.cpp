#include "MapComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
//#include "GameObject.h"

MapComponent::MapComponent()
	: m_SquareSize{ 20 }
	, m_LevelSizeX{ 30 }
	, m_LevelSizeY{ 26 }
{
}

void MapComponent::Update(float deltaTime)
{
	(void)deltaTime;
}

bool MapComponent::LoadMap(const std::string fileToLoad)
{
	bool levelLoaded{ false };

	char c;

	m_LevelFile.open(fileToLoad);
	if (m_LevelFile.is_open())
	{
		for (int y{ 0 }; y < m_LevelSizeY; ++y)
		{
			for (int x{ 0 }; x < m_LevelSizeX; ++x)
			{
				c = (char)m_LevelFile.get();
				if (c == 'X')
				{
					Object newObject{true, x*m_SquareSize, y*m_SquareSize};
					m_VectorGrid.push_back(newObject);
				}
			}
		}
		levelLoaded = true;
	}

	return levelLoaded;
}

Object::Object(bool isWall, float xPos, float yPos)
	: m_IsWall{ isWall }
	, m_XPos{ xPos }
	, m_YPos{ yPos }
{
}
