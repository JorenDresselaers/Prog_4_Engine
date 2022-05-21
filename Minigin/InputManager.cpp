#include "MiniginPCH.h"
#include "InputManager.h"

struct dae::InputManager::Impl
{
    Impl()
        : ButtonState{ false }
        , ButtonPreviousState{ false }
    {}

    ~Impl()
    {
        delete ButtonA;
        delete ButtonB;
        delete ButtonX;
        delete ButtonY;
    }

    bool ProcessInput()
    {
        // todo: read the input
        //std::cout << ButtonState[0];

        DWORD dwResult;
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        dwResult = XInputGetState(0, &state);
        if (dwResult == ERROR_SUCCESS)
        {
            if (IsPressed(dae::ControllerButton::ButtonA)) ButtonA->Execute();
            if (IsPressed(dae::ControllerButton::ButtonB)) ButtonB->Execute();
            if (IsPressed(dae::ControllerButton::ButtonX)) ButtonX->Execute();
            if (IsPressed(dae::ControllerButton::ButtonY)) ButtonY->Execute();
        }
        else
        {
            //std::cout << "\nNo controller connected :(";
        }

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                return false;
            }
            if (e.type == SDL_KEYDOWN) {

            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {

            }
        }
        return true;
    }

    bool IsPressed(ControllerButton button)
    {
        bool boolToReturn{ false };
        ButtonPreviousState[int(button)] = ButtonState[int(button)];
        ButtonState[int(button)] = false;

        DWORD dwResult;
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                boolToReturn = false;
            }
            if (e.type == SDL_KEYDOWN) {

            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {

            }
        }

        dwResult = XInputGetState(0, &state);
        if (dwResult == ERROR_SUCCESS)
        {
            if (state.Gamepad.wButtons)
            {
                switch (button)
                {
                case dae::ControllerButton::ButtonA:
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
                    {
                        ButtonState[int(ControllerButton::ButtonA)] = true;
                        if (!ButtonPreviousState[int(ControllerButton::ButtonA)] && ButtonState[int(ControllerButton::ButtonA)])
                        {
                            boolToReturn = true;
                        }
                    }
                    break;
                case dae::ControllerButton::ButtonB:
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
                    {
                        ButtonState[int(ControllerButton::ButtonB)] = true;
                        if (!ButtonPreviousState[int(ControllerButton::ButtonB)] && ButtonState[int(ControllerButton::ButtonB)])
                        {
                            boolToReturn = true;
                        }
                    }
                    break;
                case dae::ControllerButton::ButtonX:
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
                    {
                        ButtonState[int(ControllerButton::ButtonX)] = true;
                        if (!ButtonPreviousState[int(ControllerButton::ButtonX)] && ButtonState[int(ControllerButton::ButtonX)])
                        {
                            boolToReturn = true;
                        }
                    }
                    break;
                case dae::ControllerButton::ButtonY:
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
                    {
                        ButtonState[int(ControllerButton::ButtonY)] = true;
                        if (!ButtonPreviousState[int(ControllerButton::ButtonY)] && ButtonState[int(ControllerButton::ButtonY)])
                        {
                            boolToReturn = true;
                        }
                    }
                    break;
                case dae::ControllerButton::ButtonLeft:
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
                    {
                        ButtonState[int(ControllerButton::ButtonLeft)] = true;
                        if (!ButtonPreviousState[int(ControllerButton::ButtonLeft)] && ButtonState[int(ControllerButton::ButtonLeft)])
                        {
                            boolToReturn = true;
                        }
                    }
                    break;
                case dae::ControllerButton::ButtonRight:
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
                    {
                        ButtonState[int(ControllerButton::ButtonRight)] = true;
                        if (!ButtonPreviousState[int(ControllerButton::ButtonRight)] && ButtonState[int(ControllerButton::ButtonRight)])
                        {
                            boolToReturn = true;
                        }
                    }
                    break;
                case dae::ControllerButton::ButtonUp:
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
                    {
                        ButtonState[int(ControllerButton::ButtonUp)] = true;
                        if (!ButtonPreviousState[int(ControllerButton::ButtonUp)] && ButtonState[int(ControllerButton::ButtonUp)])
                        {
                            boolToReturn = true;
                        }
                    }
                    break;
                case dae::ControllerButton::ButtonDown:
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
                    {
                        ButtonState[int(ControllerButton::ButtonDown)] = true;
                        if (!ButtonPreviousState[int(ControllerButton::ButtonDown)] && ButtonState[int(ControllerButton::ButtonDown)])
                        {
                            boolToReturn = true;
                        }
                    }
                    break;
                case dae::ControllerButton::ButtonLeftShoulder:
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
                    {
                        ButtonState[int(ControllerButton::ButtonLeftShoulder)] = true;
                        if (!ButtonPreviousState[int(ControllerButton::ButtonLeftShoulder)] && ButtonState[int(ControllerButton::ButtonLeftShoulder)])
                        {
                            boolToReturn = true;
                        }
                    }
                    break;
                case dae::ControllerButton::ButtonRightShoulder:
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
                    {
                        ButtonState[int(ControllerButton::ButtonRightShoulder)] = true;
                        if (!ButtonPreviousState[int(ControllerButton::ButtonRightShoulder)] && ButtonState[int(ControllerButton::ButtonRightShoulder)])
                        {
                            boolToReturn = true;
                        }
                    }
                    break;
                case dae::ControllerButton::ButtonRightThumb:
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
                    {
                        ButtonState[int(ControllerButton::ButtonRightThumb)] = true;
                        if (!ButtonPreviousState[int(ControllerButton::ButtonRightThumb)] && ButtonState[int(ControllerButton::ButtonRightThumb)])
                        {
                            boolToReturn = true;
                        }
                    }
                    break;
                case dae::ControllerButton::ButtonLeftThumb:
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
                    {
                        ButtonState[int(ControllerButton::ButtonLeftThumb)] = true;
                        if (!ButtonPreviousState[int(ControllerButton::ButtonLeftThumb)] && ButtonState[int(ControllerButton::ButtonLeftThumb)])
                        {
                            boolToReturn = true;
                        }
                    }
                    break;
                case dae::ControllerButton::ButtonBack:
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
                    {
                        ButtonState[int(ControllerButton::ButtonBack)] = true;
                        if (!ButtonPreviousState[int(ControllerButton::ButtonBack)] && ButtonState[int(ControllerButton::ButtonBack)])
                        {
                            boolToReturn = true;
                        }
                    }
                    break;
                case dae::ControllerButton::ButtonStart:
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
                    {
                        ButtonState[int(ControllerButton::ButtonStart)] = true;
                        if (!ButtonPreviousState[int(ControllerButton::ButtonStart)] && ButtonState[int(ControllerButton::ButtonStart)])
                        {
                            boolToReturn = true;
                        }
                    }
                    break;
                default:
                    return false;
                    break;
                }
            }
        }

        return boolToReturn;
    }

    static const int m_NumberOfButtons{ 14 };
    bool ButtonState[m_NumberOfButtons];
    bool ButtonPreviousState[m_NumberOfButtons];

    Command* ButtonA = new Fire();
    Command* ButtonB = new Jump();
    Command* ButtonX = new Crouch();
    Command* ButtonY = new Die();
};

dae::InputManager::InputManager()
    : pimpl{ new Impl() }
{
}

bool dae::InputManager::ProcessInput()
{
    return pimpl->ProcessInput();
}

/*
bool dae::InputManager::ProcessInput()
{
    ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
    XInputGetState(0, &m_CurrentState);

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            return false;
        }
        if (e.type == SDL_KEYDOWN) {

        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {

        }
    }

    return true;
}
*/

bool dae::InputManager::IsPressed(ControllerButton button)
{
    return pimpl->IsPressed(button);
}

dae::InputManager::~InputManager()
{
}



//bool dae::InputManager::IsPressed(ControllerButton button) const
//{
//	switch (button)
//	{
//	case ControllerButton::ButtonA:
//		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
//	case ControllerButton::ButtonB:
//		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
//	case ControllerButton::ButtonX:
//		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
//	case ControllerButton::ButtonY:
//		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
//	default: return false;
//	}
//}

