#include "ScoreComponent.h"

ScoreComponent::ScoreComponent()
	: m_Score{ 0 }
{
}

void ScoreComponent::SetScore(int newScore)
{
	m_Score = newScore;
}

int ScoreComponent::GetScore() const
{
	return m_Score;
}
