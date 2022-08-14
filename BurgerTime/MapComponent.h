#pragma once
#include <Component.h>
#include <vector>
#include <fstream>
#pragma warning( disable : 4201)

enum class Square
{
    empty,
    wall
};

class Object
{
public:
    Object(bool isWall, float xPos, float yPos);
    bool m_IsWall;
    float m_XPos, m_YPos;
};

class MapComponent : public Component
{
public:
    MapComponent();
    ~MapComponent() = default;

    bool LoadMap(const std::string fileToLoad);

private:
    std::ifstream m_LevelFile;
    std::vector<Object> m_VectorGrid;
    int m_LevelSizeX, m_LevelSizeY;
    float m_SquareSize;
};
