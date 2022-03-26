#ifndef GRAPHICS_LAB_FREETYPE_H
#define GRAPHICS_LAB_FREETYPE_H

#include <ft2build.h>
#include <vector>
#include FT_FREETYPE_H

using std::string;
using std::vector;


class FreeTypeManager {
public:
	explicit FreeTypeManager(string filePath);
	FT_Face GetFace();
};