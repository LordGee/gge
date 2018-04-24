#include "Font.h"

namespace gge
{
	namespace graphics
	{
		Font::Font(std::string name, std::string file, unsigned size) 
			: m_FontName(name), m_FontFile(file), m_FontSize(size)
		{
			m_Atlas = ftgl::texture_atlas_new(512, 512, 2);
			m_Font = ftgl::texture_font_new_from_file(m_Atlas, m_FontSize, m_FontFile.c_str());
		}

		void Font::SetScale(float x, float y) {
			m_Scale = maths::Vector2(x, y);
		}
	}
}