#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"

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
		InputManager& operator=(InputManager rhs) = delete;

		bool ProcessInput();
		bool IsPressed(ControllerButton button);
	private:
		XINPUT_STATE m_CurrentState{};
		struct Impl;
		std::unique_ptr<Impl> pimpl;
	};

}
