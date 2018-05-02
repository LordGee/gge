#include "FontManager.h"

namespace gge
{
	namespace graphics
	{
		std::vector<Font*> FontManager::m_Fonts;

		void FontManager::FontManagerInit() {
			/* Apply a default font to the Font Renderer */
			AddFont(new Font("Default", "font/arial.ttf", 32));
		}

		void FontManager::AddFont(Font* font) {
			/* Add a new font to the font array */
			m_Fonts.push_back(font);
		}

		Font* FontManager::GetFont() {
			/* Returns the default font */
			return m_Fonts[0];
		}

		Font* FontManager::GetFont(const std::string& name) {
			/* Iterate through looking for the font by name */
			for (int i = 0; i < m_Fonts.size(); i++) {
				if (m_Fonts[i]->GetFontName() == name) {
					/* If found return the desired font */
					return m_Fonts[i];
				}
			}
			/* Else return the default font */
			return m_Fonts[0];
		}

		Font* FontManager::GetFont(const std::string& name, unsigned int size) {
			/* Iterate through looking for the font by name and size */
			for (int i = 0; i < m_Fonts.size(); i++) {
				if (m_Fonts[i]->GetFontSize() == size && m_Fonts[i]->GetFontName() == name) {
					/* If found return the desired font */
					return m_Fonts[i];
				}
			}
			/* Else return the default font */
			return m_Fonts[0];
		}

		void FontManager::TeminateAllFonts() {
			/* Iterate through and delete all fonts */
			for (int i = 0; i < m_Fonts.size(); i++) {
				delete m_Fonts[i];
			}
		}
		
		FontManager::FontManager() { }
	}
}
