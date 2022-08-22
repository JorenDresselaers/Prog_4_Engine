#pragma once
#include "Singleton.h"

class ScoreManager final : public dae::Singleton<ScoreManager>
{
public:
	ScoreManager();
	~ScoreManager();
	ScoreManager(const ScoreManager& other) = delete;
	ScoreManager(ScoreManager&& other) = delete;
	ScoreManager& operator=(const ScoreManager& other) = delete;
	ScoreManager& operator=(ScoreManager&& other) = delete;

	void AddScore(int scoreToAdd);
	int GetScore() const;
private:
	int m_Score;
};

