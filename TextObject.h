#pragma once
#include <string>
#include <memory>
#include "GameObject.h"
#include "TransformComponent.h"

namespace dae
{
	class Font;
	class Texture2D;
	//TODO: rewrite as a component
	class TextComponent final : public GameObject
	{
	public:
		void Update() override;
		void Render() const override;

		void SetText(const std::string& text);

		void SetPosition(const float x, const float y);

		TextComponent(const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool m_needsUpdate;
		std::string m_text;
		//TODO: TransformComponent m_transform{};
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
	};
}
