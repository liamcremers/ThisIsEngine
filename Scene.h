#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace dae
{
    class Scene final
    {
        friend Scene& SceneManager::CreateScene(const std::string& name);

    public:
        void Add(std::unique_ptr<GameObject> object);
        void Remove(std::unique_ptr<GameObject> object);
        void RemoveAll();

        void Update();
        void FixedUpdate();
        void Render() const;
        void LateUpdate();

        void ActivateScene();
        void DeactivateScene();
        [[nodiscard]] auto GetName() const -> const std::string&;
        [[nodiscard]] auto GetGameObjects() const -> std::vector<GameObject*>;

        ~Scene() = default;
        Scene(const Scene& other) = delete;
        Scene(Scene&& other) = delete;
        Scene& operator=(const Scene& other) = delete;
        Scene& operator=(Scene&& other) = delete;

    private:
        void ProcessPendingComponentChanges();
        explicit Scene(std::string name);

        std::string m_name{};
        std::vector<GameObject*> m_pendingActivations{};
        std::vector<GameObject*> m_pendingDeactivations{};
        std::vector<std::unique_ptr<GameObject>> m_objects{};
        bool m_IsActive{};
        bool m_hasPendingChanges{};
        static unsigned int m_idCounter;
    };
}
