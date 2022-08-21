#pragma once
#include "Command.h"
#include "GameObject.h"
#include "PlayerComponent.h"

namespace dae
{
	class MoveUp final: public Command
	{
	public:
		MoveUp(GameObject* object)
			: m_pPlayer{ object }
		{}
		virtual void Execute() override
		{
			m_pPlayer->GetComponent<PlayerComponent>()->MoveUp();
		}
	private:
		GameObject* m_pPlayer;
	};

	class MoveDown final: public Command
	{
	public:
		MoveDown(GameObject* object)
			: m_pPlayer{ object }
		{}
		virtual void Execute() override
		{
			m_pPlayer->GetComponent<PlayerComponent>()->MoveDown();
		}
	private:
		GameObject* m_pPlayer;
	};

	class MoveLeft final: public Command
	{
	public:
		MoveLeft(GameObject* object)
			: m_pPlayer{ object }
		{}
		virtual void Execute() override
		{
			m_pPlayer->GetComponent<PlayerComponent>()->MoveLeft();
		}
	private:
		GameObject* m_pPlayer;
	};

	class MoveRight final: public Command
	{
	public:
		MoveRight(GameObject* object)
			: m_pPlayer{ object }
		{}
		virtual void Execute() override
		{
			m_pPlayer->GetComponent<PlayerComponent>()->MoveRight();
		}
	private:
		GameObject* m_pPlayer;
	};
}