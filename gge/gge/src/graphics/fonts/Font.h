#pragma once

#include "../../../ext/FreeType-GL/src/freetype-gl.h"
#include <string>
#include "../../maths/Vector2.h"

namespace gge
{
	namespace graphics
	{
		class Font {
		private:
			ftgl::texture_atlas_t*		m_Atlas;
			ftgl::texture_font_t*		m_Font;
			std::string					m_FontFile;
			std::string					m_FontName;
			unsigned int				m_FontSize;
			maths::Vector2				m_Scale;
			
		public:
			Font(std::string name, std::string file, unsigned int size);

			void SetScale(float x, float y);

			inline ftgl::texture_atlas_t* GetAtlas() const { return m_Atlas; }
			inline ftgl::texture_font_t* GetFont() const { return m_Font; }

			inline const unsigned int GetFontID() const { return m_Atlas->id; }
			inline const std::string& GetFontName() const { return m_FontName; }
			inline const std::string& GetFontFile() const { return m_FontFile; }
			inline const unsigned int GetFontSize() const { return m_FontSize; }
			inline const maths::Vector2& GetScale() const { return m_Scale; }

		};
	}
}
