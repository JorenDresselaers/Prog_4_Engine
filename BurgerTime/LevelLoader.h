#pragma once
#include <string>
#include <fstream>

class LevelLoader final
{
public:
	LevelLoader();
	~LevelLoader();
	LevelLoader(const LevelLoader& other) = delete;
	LevelLoader(LevelLoader&& other) = delete;
	LevelLoader& operator=(const LevelLoader& other) = delete;
	LevelLoader& operator=(LevelLoader&& other) = delete;


	bool LoadLevel(std::string levelFile, std::string scene);
	bool LoadNextLevel(std::string scene);
	void SetLevelSize(int x, int y);
	void SetBlockSize(int newSize);

private:
	std::ifstream m_LevelFile;
	int m_LevelSizeX, m_LevelSizeY;
	int m_BlockSize, m_LevelOffsetY;

	std::string m_NextLevel;
};

