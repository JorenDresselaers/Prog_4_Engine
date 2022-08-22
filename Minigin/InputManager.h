#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"
#include "Game.h"

#include <map>

namespace dae
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		ButtonLeft,
		ButtonRight,
		ButtonUp,
		ButtonDown,
		ButtonLeftShoulder,
		ButtonRightShoulder,
		ButtonRightThumb,
		ButtonLeftThumb,
		ButtonBack,
		ButtonStart
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;


		bool ProcessInput();
		bool IsPressed(WORD button);
		void SetGame(Game* newGame);

		void SetCommand(WORD button, Command* command);
	private:
		XINPUT_STATE m_CurrentState{};
		struct Impl;
		std::unique_ptr<Impl> pimpl;
	};

}
