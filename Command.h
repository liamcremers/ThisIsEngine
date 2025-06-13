#pragma once

#include <glm.hpp>

namespace dae
{
    class Command
    {
    public:
        virtual void Execute() = 0;
        virtual void Undo() = 0;
    };

    class GameObject;

    class GameObjectCommand : public Command
    {
    public:
        GameObjectCommand(GameObject* pGameObject);
        virtual ~GameObjectCommand() = default;
        void Execute() override = 0;
        void Undo() override = 0;

    protected:
        [[nodiscard]]
        virtual auto GetGameObject() const -> GameObject* final;

    private:
        GameObject* m_pGameObject{};
    };
}
