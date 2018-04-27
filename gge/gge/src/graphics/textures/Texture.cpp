#include "Texture.h"

namespace gge
{
	namespace graphics
	{
		/* Only constructer for loading in new images */
		Texture::Texture(const std::string filepath)
			: m_TexturePath(filepath) {
			m_TextureID = LoadTexture();
		}

		Texture::~Texture() { }

		/* Bind the texture ID to the GL_TEXTURE_2D target */
		void Texture::BindTexture() const {
			glBindTexture(GL_TEXTURE_2D, m_TextureID);
		}

		/* Unbinds the texture ID from the GL_TEXTURE_2D target */
		void Texture::UnbindTexture() const {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		/* Load the Texture to be submitted to the renderer */
		GLuint Texture::LoadTexture() {
			/* Loads the current image using the FreeImage library */
			BYTE* pixels = LoadImage(m_TexturePath.c_str(), &m_TextureWidth, &m_TextureHeight);
			GLuint textureID;
			/* Generates and returns the texture name */
			glGenTextures(1, &textureID);
			/* Bind the texture ID to the GL_TEXTURE_2D target */
			glBindTexture(GL_TEXTURE_2D, textureID);
			/* Define the texture parameter with the texture minifying function applied */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			/* Define the texture parameter with the  texture magnification function applied */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			/* Defines the texture as a 2D texture image */
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_TextureWidth, m_TextureHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
			/* Unbinds the texture ID from the GL_TEXTURE_2D target */
			glBindTexture(GL_TEXTURE_2D, 0);
			/* Removes the copy of the image without this there is an obvious memory leak when testing larger images */
			delete[] pixels;

			return textureID;
		}
	}
}