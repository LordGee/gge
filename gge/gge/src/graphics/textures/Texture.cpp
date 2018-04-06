#include "Texture.h"

namespace gge
{
	namespace graphics
	{
		Texture::Texture(const std::string filepath)
			: m_TexturePath(filepath) {
			m_TextureID = LoadTexture();
		}

		Texture::~Texture() {
			// FreeImage_Unload(m_TextureID);
		}

		void Texture::BindTexture() const {
			glBindTexture(GL_TEXTURE_2D, m_TextureID);
		}

		void Texture::UnbindTexture() const {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		GLuint Texture::LoadTexture() {
			BYTE* pixels = LoadImage(m_TexturePath.c_str(), &m_TextureWidth, &m_TextureHeight);
			GLuint textureID;
			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_TextureWidth, m_TextureHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
			glBindTexture(GL_TEXTURE_2D, 0);
			return textureID;
		}
	}
}