#pragma once
#include <string>
#include <fstream>

class LevelLoader final
{
public:
	LevelLoader();
	~LevelLoader();

	bool LoadLevel(std::string levelFile, std::string scene);
	void SetLevelSize(int x, int y);
	void SetBlockSize(int newSize);

private:
	std::ifstream m_LevelFile;
	int m_LevelSizeX, m_LevelSizeY;
	int m_BlockSize, m_LevelOffsetY;
};

