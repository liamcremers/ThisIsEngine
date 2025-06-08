#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include <SDL_rect.h>
#include <glm.hpp>

namespace dae
{
    class SpriteComponent final : public BaseComponent
    {
    public:
        explicit SpriteComponent(GameObject& parent,
                                 float scale,
                                 glm::vec2 size);
        void Update() override;
        void Render() const override;

        void SetTexture(const std::string& filename);
        void SetAnimationSpeed(float framesPerSecond);

        void Play();
        void Pause();
        void Reset();

    private:
        void SetFrameSize(int width, int height);

        static constexpr float DEFAULT_FRAME_DURATION{ 1.f / 4.f };

        SDL_Rect m_SourceRect{};
        Texture2D* m_pTexture{};
        int m_FrameWidth{};
        int m_FrameHeight{};
        int m_Columns{};
        int m_Rows{};
        int m_CurrentFrame{};
        const float m_Scale{};
        float m_FrameTimer{};
        float m_FrameDuration{ DEFAULT_FRAME_DURATION };
        bool m_IsPaused{};
    };
}
