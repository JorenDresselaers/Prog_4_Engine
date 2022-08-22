#pragma once
#include <Component.h>
class ScoreComponent : public Component
{
public:
	ScoreComponent();
	~ScoreComponent() = default;

	void SetScore(int newScore);
	int GetScore() const;
private:
	int m_Score;
};

