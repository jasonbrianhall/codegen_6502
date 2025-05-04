#include "Controller.hpp"
#include <iostream>

Controller::Controller() : joystick(nullptr), gameController(nullptr), joystickID(-1), joystickInitialized(false)
{
    for (auto& b : buttonStates)
    {
        b = false;
    }
    buttonIndex = 0;
    strobe = 1;
}

Controller::~Controller()
{
    if (gameController != nullptr)
    {
        SDL_GameControllerClose(gameController);
    }
    else if (joystick != nullptr)
    {
        SDL_JoystickClose(joystick);
    }
}

bool Controller::initJoystick()
{
    // Make sure SDL has been initialized with joystick support
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
    {
        if (SDL_InitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0)
        {
            std::cerr << "SDL joystick subsystem could not be initialized: " << SDL_GetError() << std::endl;
            return false;
        }
    }

    // Enable joystick events
    SDL_JoystickEventState(SDL_ENABLE);
    SDL_GameControllerEventState(SDL_ENABLE);

    // Check for available joysticks
    int numJoysticks = SDL_NumJoysticks();
    if (numJoysticks <= 0)
    {
        std::cout << "No joysticks connected." << std::endl;
        return false;
    }

    // Try to open the first available joystick
    // First try to open as game controller (more standardized)
    for (int i = 0; i < numJoysticks; i++)
    {
        if (SDL_IsGameController(i))
        {
            gameController = SDL_GameControllerOpen(i);
            if (gameController)
            {
                std::cout << "Found gamepad: " << SDL_GameControllerName(gameController) << std::endl;
                joystick = SDL_GameControllerGetJoystick(gameController);
                joystickID = SDL_JoystickInstanceID(joystick);
                joystickInitialized = true;
                return true;
            }
        }
    }

    // If no game controller is available, try as generic joystick
    if (!joystickInitialized)
    {
        joystick = SDL_JoystickOpen(0);
        if (joystick)
        {
            std::cout << "Found joystick: " << SDL_JoystickName(joystick) << std::endl;
            joystickID = SDL_JoystickInstanceID(joystick);
            joystickInitialized = true;
            return true;
        }
        else
        {
            std::cerr << "Could not open joystick: " << SDL_GetError() << std::endl;
            return false;
        }
    }

    return joystickInitialized;
}

uint8_t Controller::readByte()
{
    uint8_t value = 1;

    if (buttonIndex < 8)
    {
        value = (buttonStates[buttonIndex] ? 0x41 : 0x40);
    }

    if ((strobe & (1 << 0)) == 0)
    {
        buttonIndex++;
    }

    return value;
}

void Controller::setButtonState(ControllerButton button, bool state)
{
    buttonStates[(int)button] = state;
}

void Controller::writeByte(uint8_t value)
{
    if ((value & (1 << 0)) == 0 && (strobe & (1 << 0)) == 1)
    {
        buttonIndex = 0;
    }
    strobe = value;
}

void Controller::processJoystickEvent(const SDL_Event& event)
{
    if (!joystickInitialized)
        return;

    // Handle various joystick events
    switch (event.type)
    {
        case SDL_JOYAXISMOTION:
            if (event.jaxis.which == joystickID)
            {
                // Handle X axis (left/right)
                if (event.jaxis.axis == 0)
                {
                    if (event.jaxis.value < -JOYSTICK_DEADZONE)
                    {
                        setButtonState(BUTTON_LEFT, true);
                        setButtonState(BUTTON_RIGHT, false);
                    }
                    else if (event.jaxis.value > JOYSTICK_DEADZONE)
                    {
                        setButtonState(BUTTON_RIGHT, true);
                        setButtonState(BUTTON_LEFT, false);
                    }
                    else
                    {
                        setButtonState(BUTTON_LEFT, false);
                        setButtonState(BUTTON_RIGHT, false);
                    }
                }
                // Handle Y axis (up/down)
                else if (event.jaxis.axis == 1)
                {
                    if (event.jaxis.value < -JOYSTICK_DEADZONE)
                    {
                        setButtonState(BUTTON_UP, true);
                        setButtonState(BUTTON_DOWN, false);
                    }
                    else if (event.jaxis.value > JOYSTICK_DEADZONE)
                    {
                        setButtonState(BUTTON_DOWN, true);
                        setButtonState(BUTTON_UP, false);
                    }
                    else
                    {
                        setButtonState(BUTTON_UP, false);
                        setButtonState(BUTTON_DOWN, false);
                    }
                }
            }
            break;

        case SDL_JOYBUTTONDOWN:
            if (event.jbutton.which == joystickID)
            {
                mapJoystickButtonToController(event.jbutton.button, BUTTON_A);
            }
            break;

        case SDL_JOYBUTTONUP:
            if (event.jbutton.which == joystickID)
            {
                // Default mapping for generic joysticks
                switch (event.jbutton.button)
                {
                    case 0: setButtonState(BUTTON_A, false); break;
                    case 1: setButtonState(BUTTON_B, false); break;
                    case 8: setButtonState(BUTTON_SELECT, false); break;
                    case 9: setButtonState(BUTTON_START, false); break;
                    default: break;
                }
            }
            break;

        case SDL_CONTROLLERBUTTONDOWN:
            if (event.cbutton.which == joystickID)
            {
                // GameController mapping (standardized across different controllers)
                switch (event.cbutton.button)
                {
                    case SDL_CONTROLLER_BUTTON_A:
                        setButtonState(BUTTON_A, true);
                        break;
                    case SDL_CONTROLLER_BUTTON_B:
                        setButtonState(BUTTON_B, true);
                        break;
                    case SDL_CONTROLLER_BUTTON_BACK:
                        setButtonState(BUTTON_SELECT, true);
                        break;
                    case SDL_CONTROLLER_BUTTON_START:
                        setButtonState(BUTTON_START, true);
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_UP:
                        setButtonState(BUTTON_UP, true);
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                        setButtonState(BUTTON_DOWN, true);
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                        setButtonState(BUTTON_LEFT, true);
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                        setButtonState(BUTTON_RIGHT, true);
                        break;
                }
            }
            break;

        case SDL_CONTROLLERBUTTONUP:
            if (event.cbutton.which == joystickID)
            {
                // GameController mapping
                switch (event.cbutton.button)
                {
                    case SDL_CONTROLLER_BUTTON_A:
                        setButtonState(BUTTON_A, false);
                        break;
                    case SDL_CONTROLLER_BUTTON_B:
                        setButtonState(BUTTON_B, false);
                        break;
                    case SDL_CONTROLLER_BUTTON_BACK:
                        setButtonState(BUTTON_SELECT, false);
                        break;
                    case SDL_CONTROLLER_BUTTON_START:
                        setButtonState(BUTTON_START, false);
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_UP:
                        setButtonState(BUTTON_UP, false);
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                        setButtonState(BUTTON_DOWN, false);
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                        setButtonState(BUTTON_LEFT, false);
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                        setButtonState(BUTTON_RIGHT, false);
                        break;
                }
            }
            break;

        case SDL_CONTROLLERAXISMOTION:
            if (event.caxis.which == joystickID)
            {
                // Handle left thumbstick X axis
                if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX)
                {
                    if (event.caxis.value < -JOYSTICK_DEADZONE)
                    {
                        setButtonState(BUTTON_LEFT, true);
                        setButtonState(BUTTON_RIGHT, false);
                    }
                    else if (event.caxis.value > JOYSTICK_DEADZONE)
                    {
                        setButtonState(BUTTON_RIGHT, true);
                        setButtonState(BUTTON_LEFT, false);
                    }
                    else
                    {
                        setButtonState(BUTTON_LEFT, false);
                        setButtonState(BUTTON_RIGHT, false);
                    }
                }
                // Handle left thumbstick Y axis
                else if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY)
                {
                    if (event.caxis.value < -JOYSTICK_DEADZONE)
                    {
                        setButtonState(BUTTON_UP, true);
                        setButtonState(BUTTON_DOWN, false);
                    }
                    else if (event.caxis.value > JOYSTICK_DEADZONE)
                    {
                        setButtonState(BUTTON_DOWN, true);
                        setButtonState(BUTTON_UP, false);
                    }
                    else
                    {
                        setButtonState(BUTTON_UP, false);
                        setButtonState(BUTTON_DOWN, false);
                    }
                }
            }
            break;
    }
}

void Controller::updateJoystickState()
{
    if (!joystickInitialized)
        return;

    // This function can be used to poll joystick state directly
    // instead of relying on events, if needed
    
    // For instance, if you're using GameController and want to check button states:
    if (gameController)
    {
        // Example of polling controller buttons directly
        // Uncomment if you need to poll buttons separately from events
        /*
        setButtonState(BUTTON_A, SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_A));
        setButtonState(BUTTON_B, SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_B));
        setButtonState(BUTTON_SELECT, SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_BACK));
        setButtonState(BUTTON_START, SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_START));
        
        // D-pad
        setButtonState(BUTTON_UP, SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_DPAD_UP));
        setButtonState(BUTTON_DOWN, SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_DPAD_DOWN));
        setButtonState(BUTTON_LEFT, SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_DPAD_LEFT));
        setButtonState(BUTTON_RIGHT, SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_DPAD_RIGHT));
        */
    }
}

void Controller::mapJoystickButtonToController(int button, ControllerButton nesButton)
{
    // Default mapping for generic joysticks
    // This can be customized or loaded from a configuration file
    switch (button)
    {
        case 0: setButtonState(BUTTON_A, true); break;
        case 1: setButtonState(BUTTON_B, true); break;
        case 8: setButtonState(BUTTON_SELECT, true); break;
        case 9: setButtonState(BUTTON_START, true); break;
        default: break;
    }
}
