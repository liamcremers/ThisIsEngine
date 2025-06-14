#include "Scene.h"
#include "CollisionSystem.h"
#include "EngineInputComponent.h"
#include <algorithm>
#include <ranges>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(std::string name) :
    m_name(std::move(name))
{}

void Scene::Add(std::unique_ptr<GameObject> object)
{
    m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
    auto it = std::ranges::find(m_objects, object);
    if (it != m_objects.end())
    {
        m_objects.erase(it);
    }
}

void Scene::RemoveAll() { m_objects.clear(); }

void Scene::Update()
{
    if (!m_IsActive)
        return;

    for (auto& object : m_objects)
    {
        object->Update();
    }
}

void dae::Scene::FixedUpdate()
{
    if (!m_IsActive)
        return;

    for (auto& object : m_objects)
    {
        object->FixedUpdate();
    }
}

void Scene::Render() const
{
    if (!m_IsActive)
        return;

    for (const auto& object : m_objects)
    {
        object->Render();
    }
}

void dae::Scene::LateUpdate()
{
    if (!m_IsActive)
        return;

    for (auto& object : m_objects)
        object->LateUpdate();

    ProcessPendingComponentChanges();

    std::erase_if(m_objects,
                  [](const auto& object)
                  { return object->IsMarkedForDelete(); });
}

[[nodiscard]] auto dae::Scene::GetName() const -> const std::string&
{
    return m_name;
}

[[nodiscard]] auto dae::Scene::GetGameObjects() const
    -> std::vector<GameObject*>
{
    std::vector<GameObject*> gameObjects;
    gameObjects.reserve(m_objects.size());
    for (const auto& obj : m_objects)
    {
        gameObjects.push_back(obj.get());
    }
    return gameObjects;
}

void dae::Scene::ActivateScene()
{
    if (m_IsActive)
        return;

    for (auto& go : m_objects)
        m_pendingActivations.push_back(go.get());

    m_hasPendingChanges = true;
    m_IsActive = true;
}

void dae::Scene::DeactivateScene()
{
    if (!m_IsActive)
        return;

    for (auto& go : m_objects)
        m_pendingDeactivations.push_back(go.get());

    m_hasPendingChanges = true;
    m_IsActive = false;
}

void dae::Scene::ProcessPendingComponentChanges()
{
    if (!m_hasPendingChanges)
        return;

    for (auto* go : m_pendingDeactivations)
    {
        if (auto* collider = go->GetComponent<ColliderComponent>())
            dae::CollisionSystem::GetInstance().UnRegisterCollider(collider);

        if (auto* input = go->GetComponentOfType<EngineInputComponent>())
            input->Deactivate();
    }

    for (auto* go : m_pendingActivations)
    {
        if (auto* collider = go->GetComponent<ColliderComponent>())
            dae::CollisionSystem::GetInstance().RegisterCollider(collider);

        if (auto* input = go->GetComponentOfType<EngineInputComponent>())
            input->Activate();
    }

    m_pendingActivations.clear();
    m_pendingDeactivations.clear();
    m_hasPendingChanges = false;
}
