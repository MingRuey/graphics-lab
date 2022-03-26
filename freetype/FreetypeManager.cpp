
#include "FreetypeManager.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>


FreeTypeManager::FreeTypeManager(const string filePath, int pixelSize) 
{
	if (FT_Init_FreeType(&library)) {
		std::cout << "Could not init freetype library" << std::endl;
		exit(1);
	}
	if (FT_New_Face(library, &filePath[0], 0, &face)) {
		std::cout << "Fail to load font:"<< filePath << std::endl;
		exit(1);
	}
	FT_Set_Pixel_Sizes(face, 0, pixelSize);
}

FT_GlyphSlot FreeTypeManager::LoadChar(unsigned char c) {
	if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
		std::cout << "Fail to load char:"<< c << std::endl;
		exit(1);
	}
	return face->glyph;
}

void FreeTypeManager::StoreCharTexture(unsigned char c, unsigned int textureId, FT_GlyphSlot glyph) {
	CharTextureData charData = {
		textureId,
		glm::ivec2(glyph->bitmap.width, glyph->bitmap.rows),
		glm::ivec2(glyph->bitmap_left, glyph->bitmap_top),
		glyph->advance.x
	};
	charMap.insert(std::pair<char, CharTextureData>(c, charData));
}

void FreeTypeManager::FreeFace() {
	FT_Done_Face(face);
	FT_Done_FreeType(library);
}
