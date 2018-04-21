#pragma once

#include "../renderables/Renderable2D.h"

namespace gge
{
	namespace graphics
	{
		class Text : public Renderable2D {
		public:
			Font *				font;
			std::string			text;
			maths::Vector3&		position;
			float				x, y;

		public:
			Text(std::string text, float x, float y, unsigned int colour);
			Text(std::string text, float x, float y, Font* font, unsigned int colour);
			Text(std::string text, float x, float y, const std::string& font, unsigned int colour);
			Text(std::string text, float x, float y, const std::string& font, unsigned int size, unsigned int colour);

			void Submit(Renderer2D* renderer) const override;

		};
	}
}