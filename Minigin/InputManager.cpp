#include "MiniginPCH.h"
#include "InputManager.h"
#include "AudioManager.h"

struct dae::InputManager::Impl
{
    Impl()
        : game{ nullptr }
    {}

    ~Impl()
    {
        for (auto currentCommand : m_CommandMap)
        {
            delete currentCommand.second;
            currentCommand.second = nullptr;
        }
    }

    void SetGame(Game* newGame)
    {
        game = newGame;
    }

    bool ProcessInput()
    {
        DWORD dwResult;
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        //controller input
        dwResult = XInputGetState(0, &state);
        if (dwResult == ERROR_SUCCESS)
        {
            for (auto currentButton = m_CommandMap.begin(); currentButton != m_CommandMap.end(); ++currentButton)
            {
                WORD button = currentButton->first;
                if (IsPressed(button))
                {
                    std::cout << "\nExecuting " << button;
                    m_CommandMap[button]->Execute();
                }
            }
        }
        else
        {
            //std::cout << "\nNo controller connected :(";
        }

        //keyboard input
        SDL_Event e{};
        while (SDL_PollEvent(&e)) 
        {
            switch (e.type)
            {
            case SDL_QUIT:
                return false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                game->ProcessMouseDown(e.button);
                break;

            case SDL_MOUSEBUTTONUP:
                game->ProcessMouseUp(e.button);
                break;

            case SDL_KEYDOWN:
                game->ProcessKeyDown(e.key);
                break;

            case SDL_KEYUP:
                game->ProcessKeyUp(e.key);
                break;
            }
        }

        return true;
    }

    //https://stackoverflow.com/questions/38863451/xbox-button-pressed-in-c
    bool IsPressed(WORD button)
    {
        DWORD dwResult;
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        dwResult = XInputGetState(0, &state);
        if (dwResult == ERROR_SUCCESS)
        {
            return (state.Gamepad.wButtons & button) != 0;

            /*
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
            */
        }

        return false;
    }

    void SetCommand(WORD button, Command* command)
    {
        m_CommandMap[button] = command;
    }

    Game* game;

    std::map<WORD, Command*> m_CommandMap;
};

dae::InputManager::InputManager()
    : pimpl{ new Impl() }
{
}

bool dae::InputManager::ProcessInput()
{
    return pimpl->ProcessInput();
}

bool dae::InputManager::IsPressed(WORD button)
{
    return pimpl->IsPressed(button);
}

void dae::InputManager::SetGame(Game* newGame)
{
    pimpl->SetGame(newGame);
}

void dae::InputManager::SetCommand(WORD button, Command* command)
{
    pimpl->SetCommand(button, command);
}

dae::InputManager::~InputManager()
{
}
