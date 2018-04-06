#pragma once

#include <glew.h>
#include <string>
#include <FreeImage.h>
#include "../../utilities/ImageLoader.h"

namespace gge
{
	namespace graphics
	{
		class Texture {
		private:
			std::string		m_TexturePath;
			GLuint			m_TextureID;
			GLsizei			m_TextureWidth;
			GLsizei			m_TextureHeight;

		public:
			Texture(const std::string filepath);
			~Texture();
			void BindTexture() const;
			void UnbindTexture() const;

			inline const unsigned int GetWidth() const { return m_TextureWidth; }
			inline const unsigned int GetHeight() const { return m_TextureHeight; }
			inline const unsigned int GetTextureID() const { return m_TextureID; }

		private:
			GLuint LoadTexture();
		};
	}
}