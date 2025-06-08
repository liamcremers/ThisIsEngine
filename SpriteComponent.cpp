#include "SpriteComponent.h"
#include "EngineTime.h"
#include "GameObject.h"
#include "ResourceManager.h"

dae::SpriteComponent::SpriteComponent(GameObject& parent,
                                      float scale,
                                      glm::vec2 size) :
    BaseComponent(parent),
    m_Scale(scale)
{
    SetFrameSize(static_cast<int>(size.x), static_cast<int>(size.y));
}

void dae::SpriteComponent::SetTexture(const std::string& filename)
{
    m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
    if (!m_pTexture->IsScaled())
        m_pTexture->Scale(m_Scale);
    if (m_pTexture && m_FrameWidth > 0 && m_FrameHeight > 0)
    {
        m_Columns = m_pTexture->GetSize()[0] / m_FrameWidth;
        m_Rows = m_pTexture->GetSize()[1] / m_FrameHeight;
    }
}

void dae::SpriteComponent::SetFrameSize(int width, int height)
{
    m_FrameWidth = static_cast<int>(width * m_Scale);
    m_FrameHeight = static_cast<int>(height * m_Scale);
    if (m_pTexture)
    {
        m_Columns = m_pTexture->GetSize()[0] / m_FrameWidth;
        m_Rows = m_pTexture->GetSize()[1] / m_FrameHeight;
    }
}

void dae::SpriteComponent::SetAnimationSpeed(float framesPerSecond)
{
    m_FrameDuration = 1.f / framesPerSecond;
}

void dae::SpriteComponent::Play() { m_IsPaused = false; }

void dae::SpriteComponent::Pause() { m_IsPaused = true; }

void dae::SpriteComponent::Reset()
{
    m_CurrentFrame = 0;
    m_FrameTimer = 0.f;
}

void dae::SpriteComponent::Update()
{
    auto deltaTime = EngineTime::GetInstance().GetDeltaTime();

    if (m_IsPaused || m_Columns == 0 || m_Rows == 0)
        return;

    m_FrameTimer += deltaTime;
    if (m_FrameTimer >= m_FrameDuration)
    {
        m_FrameTimer = 0.f;
        m_CurrentFrame = (m_CurrentFrame + 1) % (m_Columns * m_Rows);
    }
}

void dae::SpriteComponent::Render() const
{
    if (!m_pTexture || m_FrameWidth == 0 || m_FrameHeight == 0)
        return;

    int x = (m_CurrentFrame % m_Columns) * m_FrameWidth;
    int y = (m_CurrentFrame / m_Columns) * m_FrameHeight;
    const SDL_Rect sourceRect{ x, y, m_FrameWidth, m_FrameHeight };

    const auto& pos = GetOwner().GetWorldPosition();
    const SDL_Rect destRect{ static_cast<int>(pos.x),
                             static_cast<int>(pos.y),
                             m_FrameWidth,
                             m_FrameHeight };

    Renderer::GetInstance().RenderTexture(*m_pTexture, sourceRect, destRect);
}
