#include "FontManager.h"

namespace gge
{
	namespace graphics
	{
		std::vector<Font*> FontManager::m_Fonts;

		void FontManager::FontManagerInit() {
			AddFont(new Font("Default", "font/arial.ttf", 32));
		}

		void FontManager::AddFont(Font* font) {
			m_Fonts.push_back(font);
		}

		Font* FontManager::GetFont() {
			return m_Fonts[0];
		}

		Font* FontManager::GetFont(const std::string& name) {
			for (int i = 0; i < m_Fonts.size(); i++) {
				if (m_Fonts[i]->GetFontName() == name) {
					return m_Fonts[i];
				}
			}
			return m_Fonts[0];
		}

		Font* FontManager::GetFont(const std::string& name, unsigned int size) {
			for (int i = 0; i < m_Fonts.size(); i++) {
				if (m_Fonts[i]->GetFontSize() == size && m_Fonts[i]->GetFontName() == name) {
					return m_Fonts[i];
				}
			}
			return m_Fonts[0];
		}

		void FontManager::TeminateAllFonts() {
			for (int i = 0; i < m_Fonts.size(); i++) {
				delete m_Fonts[i];
			}
		}

		FontManager::FontManager() { }
	}
}
