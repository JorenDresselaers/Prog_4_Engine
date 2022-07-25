#include "MiniginPCH.h"
#include "InputManager.h"
#include "AudioManager.h"

struct dae::InputManager::Impl
{
    Impl()
        : ButtonState{ false }
        , ButtonPreviousState{ false }
        , MovingLeft{false}
        , MovingRight{false}
        , MovingDown{false}
        , MovingUp{false}
        , MovingLeftTwo{false}
        , MovingRightTwo{false}
        , MovingDownTwo{false}
        , MovingUpTwo{false}
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
        while (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_QUIT) 
            {
                return false;
            }
            if (e.type == SDL_KEYDOWN) 
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_LEFT:
                    MovingLeft = true;
                    break;
                
                case SDLK_RIGHT:
                    MovingRight = true;
                    break;
                
                case SDLK_UP:
                    MovingUp = true;
                    break;
                
                case SDLK_DOWN:
                    MovingDown = true;
                    break;

                case SDLK_w:
                    MovingUpTwo = true;
                    break;
                case SDLK_s:
                    MovingDownTwo = true;
                    break;
                case SDLK_a:
                    MovingLeftTwo = true;
                    break;
                case SDLK_d:
                    MovingRightTwo = true;
                    break;

                }
            }

            if (e.type == SDL_KEYUP)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_LEFT:
                    MovingLeft = false;
                    break;

                case SDLK_RIGHT:
                    MovingRight = false;
                    break;

                case SDLK_UP:
                    MovingUp = false;
                    break;

                case SDLK_DOWN:
                    MovingDown = false;
                    break;

                case SDLK_w:
                    MovingUpTwo = false;
                    break;
                case SDLK_s:
                    MovingDownTwo = false;
                    break;
                case SDLK_a:
                    MovingLeftTwo = false;
                    break;
                case SDLK_d:
                    MovingRightTwo = false;
                    break;
                }
            }

            if (e.type == SDL_MOUSEBUTTONDOWN) 
            {
                AudioManager::GetInstance().Play("Fishfight.wav", 100);
            }
        }

        if (player)
        {
            if (MovingLeft) player->MoveLeft();
            if (MovingRight) player->MoveRight();
            if (MovingDown) player->MoveDown();
            if (MovingUp) player->MoveUp();
        }

        if (playerTwo)
        {
            if (MovingLeftTwo) playerTwo->MoveLeft();
            if (MovingRightTwo) playerTwo->MoveRight();
            if (MovingDownTwo) playerTwo->MoveDown();
            if (MovingUpTwo) playerTwo->MoveUp();
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

        //SDL_Event e;
        //while (SDL_PollEvent(&e)) {
        //    if (e.type == SDL_QUIT) {
        //        boolToReturn = false;
        //    }
        //    if (e.type == SDL_KEYDOWN) {
        //
        //    }rg
        //    if (e.type == SDL_MOUSEBUTTONDOWN) {
        //
        //    }
        //}



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

    bool MovingLeft;
    bool MovingRight;
    bool MovingUp;
    bool MovingDown;
    bool MovingLeftTwo;
    bool MovingRightTwo;
    bool MovingUpTwo;
    bool MovingDownTwo;

    Command* ButtonA = new Fire();
    Command* ButtonB = new Jump();
    Command* ButtonX = new Crouch();
    Command* ButtonY = new Die();

    std::shared_ptr<PlayerComponent> player;
    std::shared_ptr<PlayerComponent> playerTwo;
};

dae::InputManager::InputManager()
    : pimpl{ new Impl() }
{
}

bool dae::InputManager::ProcessInput()
{
    return pimpl->ProcessInput();
}

bool dae::InputManager::IsPressed(ControllerButton button)
{
    return pimpl->IsPressed(button);
}

void dae::InputManager::SetPlayer(std::shared_ptr<PlayerComponent> player)
{
    pimpl->player = player;

}

void dae::InputManager::SetPlayerTwo(std::shared_ptr<PlayerComponent> player)
{
    pimpl->playerTwo = player;
}

dae::InputManager::~InputManager()
{
}
