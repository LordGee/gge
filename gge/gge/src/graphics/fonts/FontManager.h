#pragma once

#include <vector>
#include "Font.h"

namespace gge
{
	namespace graphics
	{
		class FontManager {
		private:
			static std::vector<Font*>		m_Fonts;

		public:
			static void FontManagerInit();
			static void AddFont(Font* font);
			static Font* GetFont();
			static Font* GetFont(const std::string& name);
			static Font* GetFont(const std::string& name, unsigned int size);
			static void TeminateAllFonts();

		private:
			FontManager();

		};
	}
}