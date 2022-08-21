#pragma once
#include "Singleton.h"

class ScoreManager final : public dae::Singleton<ScoreManager>
{
public:
	ScoreManager();
	~ScoreManager();

	void AddScore(int scoreToAdd);
	int GetScore();
private:
	int m_Score;
};

