#include "ScoreManager.h"

ScoreManager::ScoreManager()
	:m_Score{ 0 }
{
}

ScoreManager::~ScoreManager()
{
}

void ScoreManager::AddScore(int scoreToAdd)
{
	m_Score += scoreToAdd;
}

int ScoreManager::GetScore()
{
	return m_Score;
}
