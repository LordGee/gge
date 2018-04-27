#pragma once

#include <FreeImage.h>

namespace gge
{
	/* Loads the image using FreeType */
	/* Following code is a modification of the Example texture manager provided */
	/* Ref: https://github.com/leapmotion/FreeImage/blob/master/Examples/OpenGL/TextureManager/TextureManager.cpp */
	static BYTE* LoadImage(const char* filename, GLsizei* width, GLsizei* height) {
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP * dib = nullptr;
		fif = FreeImage_GetFileType(filename, 0);
		if (fif == FIF_UNKNOWN) {
			fif = FreeImage_GetFIFFromFilename(filename);
		}
		if (fif == FIF_UNKNOWN) {
			return nullptr;
		}
		if (FreeImage_FIFSupportsReading(fif)) {
			dib = FreeImage_Load(fif, filename);
		}
		if (!dib) {
			return nullptr;
		}
		BYTE * pixels = FreeImage_GetBits(dib);
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);
		int bits = FreeImage_GetBPP(dib);
		int size = *width * *height * (bits / 8);
		BYTE* result = new BYTE[size];
		memcpy(result, pixels, size);
		FreeImage_Unload(dib);
		return result;
	}
}