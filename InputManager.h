#pragma once
#include "Singleton.h"

#include <vector>
#include <unordered_map>

typedef int SDL_Keycode;

namespace dae
{
#ifdef WIN32
    class Controller;
#endif // WIN32
    class Command;

    class InputManager final : public Singleton<InputManager>
    {
    public:
        [[nodiscard]] auto ProcessInput() -> bool;

#ifdef WIN32
        void AddController(Controller* controller);
#endif // WIN32
        void AddKeyboardCommand(SDL_Keycode keyboardButton, Command* command);

    private:
        friend class Singleton<InputManager>;
        InputManager() = default;

#ifdef WIN32
        std::vector<Controller*> m_ControllerVec;
#endif // WIN32
        std::unordered_map<SDL_Keycode, Command*> m_KeyCommandMap;
    };
}