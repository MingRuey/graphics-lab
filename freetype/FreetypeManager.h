#ifndef GRAPHICS_LAB_FREETYPE_H
#define GRAPHICS_LAB_FREETYPE_H

#include <ft2build.h>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <map>
#include FT_FREETYPE_H

using std::string;
using std::vector;

struct CharTextureData {
	unsigned int textureId;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
};

class FreeTypeManager {
public:
	/// <summary>
	/// Input argument is the height size and width will be auto calculated.
	/// </summary>
	/// <param name="filePath"></param>
	/// <param name="pixelSize"></param>
	explicit FreeTypeManager(string filePath, int pixelSize);
	FT_Face face;
	FT_GlyphSlot LoadChar(unsigned char c);
	void StoreCharTexture(unsigned char c, unsigned int textureId, FT_GlyphSlot glyph);
	void FreeFace();
	std::map<char, CharTextureData> charMap;
private:
	FT_Library library;
};

#endif