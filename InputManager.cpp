#include "InputManager.h"
#include "Command.h"
#include "Controller.h"

#include <SDL.h>
#ifdef WIN32
#include <backends/imgui_impl_sdl2.h>
#endif // WIN32
#include <ranges>
#include <algorithm>

auto dae::InputManager::ProcessInput() -> bool
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
#ifdef WIN32
        ImGui_ImplSDL2_ProcessEvent(&e);
#endif //WIN32

        if (e.type == SDL_QUIT)
            return false;

        for (auto& [key, command] : m_KeyCommandMap)
        {
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == key)
                command->Execute();
            else if (e.type == SDL_KEYUP && e.key.keysym.sym == key)
                command->Undo();
        }
    }

#ifdef WIN32
    std::ranges::for_each(m_ControllerVec, &Controller::ProcessInput);
#endif // WIN32
    return true;
}

#ifdef WIN32
void dae::InputManager::AddController(Controller* controller)
{
    if (m_ControllerVec.size() < 2)
        m_ControllerVec.emplace_back(controller);
}
#endif // WIN32
#ifndef WIN32
void dae::InputManager::AddController(Controller*) {}
#endif // !WIN32

void dae::InputManager::AddKeyboardCommand(SDL_Keycode keyboardButton,
                                           Command* command)
{
    m_KeyCommandMap[keyboardButton] = command;
}
