#include "Font.h"

namespace gge
{
	namespace graphics
	{
		Font::Font(std::string name, std::string file, unsigned size) 
			: m_FontName(name), m_FontFile(file), m_FontSize(size)
		{
			/* Setup a new FreeType atlas */
			m_Atlas = ftgl::texture_atlas_new(512, 512, 2);
			/* Load in new font based on parameters */
			m_Font = ftgl::texture_font_new_from_file(m_Atlas, m_FontSize, m_FontFile.c_str());
		}

		void Font::SetScale(float x, float y) {
			/* Set the scale of the window this is used when renderering */
			m_Scale = maths::Vector2(x, y);
		}
	}
}