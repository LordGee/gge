#include "Text.h"
#include "FontManager.h"

namespace gge
{
	namespace graphics
	{

		Text::Text(std::string text, float x, float y, unsigned int colour)
			: Renderable(), text(text), x(x), y(y), position(m_Position), font(FontManager::GetFont("Default"))
		{
			m_Position = maths::Vector3(this->x, this->y, 0.0f);
			m_Colour = colour;
		}

		Text::Text(std::string text, float x, float y, Font* font, unsigned int colour)
			: Renderable(), text(text), x(x), y(y), position(m_Position), font(font)
		{
			m_Position = maths::Vector3(this->x, this->y, 0.0f);
			m_Colour = colour;
		}

		Text::Text(std::string text, float x, float y, const std::string& font, unsigned int colour)
			: Renderable(), text(text), x(x), y(y), position(m_Position), font(FontManager::GetFont(font))
		{
			m_Position = maths::Vector3(this->x, this->y, 0.0f);
			m_Colour = colour;
		}

		Text::Text(std::string text, float x, float y, const std::string& font, unsigned size, unsigned int colour)
			: Renderable(), text(text), x(x), y(y), position(m_Position), font(FontManager::GetFont(font, size))
		{
			m_Position = maths::Vector3(this->x, this->y, 0.0f);
			m_Colour = colour;
		}

		void Text::Submit(Renderer* renderer) const {
			/* Submitted to a special text renderering function */
			renderer->SubmitText(text, position, *font, m_Colour);
		}

	}
}
