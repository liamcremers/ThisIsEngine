#include "Command.h"
#include "GameObject.h"
#include "EngineTime.h"

dae::GameObjectCommand::GameObjectCommand(GameObject* pGameObject) :
    m_pGameObject{ pGameObject }
{}

auto dae::GameObjectCommand::GetGameObject() const -> dae::GameObject*
{
    return m_pGameObject;
}
