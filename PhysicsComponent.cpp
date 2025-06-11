#include "PhysicsComponent.h"
#include "GameObject.h"
#include "EngineTime.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"

dae::PhysicsComponent::PhysicsComponent(GameObject& parent, bool useGravity) :
    BaseComponent{ parent },
    m_pCollider{ parent.GetComponent<ColliderComponent>() },
    m_UseGravity{ useGravity }
{
    assert(m_pCollider != nullptr &&
           "PhysicsComponent requires a ColliderComponent to function");
    m_pCollider->SetCollisionType(CollisionType::Dynamic);
}

void dae::PhysicsComponent::FixedUpdate()
{
    auto fixedDelta = EngineTime::GetInstance().GetFixedTimeStep();

    if (m_UseGravity)
    {
        m_Velocity[1] = m_Gravity;
    }
    if (m_Velocity != glm::vec2{ 0, 0 })
    {
        auto x = m_Velocity[0] * fixedDelta;
        auto y = m_Velocity[1] * fixedDelta;
        if (m_UseGravity)
            y = std::max((m_Velocity[1] * fixedDelta), 1.f);
        GetOwner().SetLocalPosition(GetOwner().GetLocalPosition() +
                                    glm::vec2{ x, y });

        m_pCollider->SetHasMoved(true);
    }
}

void dae::PhysicsComponent::SetVelocity(const glm::vec2& velocity)
{
    m_Velocity = velocity;
}

void dae::PhysicsComponent::SetGravity(float gravity) { m_Gravity = gravity; }

void dae::PhysicsComponent::SetUseGravity(bool useGravity)
{
    m_UseGravity = useGravity;
}

[[nodiscard]] auto dae::PhysicsComponent::GetVelocity() const -> glm::vec2
{
    return m_Velocity;
}

[[nodiscard]] auto dae::PhysicsComponent::GetGravity() const -> float
{
    return m_Gravity;
}

[[nodiscard]] auto dae::PhysicsComponent::IsUsingGravity() const -> bool
{
    return m_UseGravity;
}
