//
// Created by mrchou on 1/23/2022.
//

#ifndef GRAPHICS_LAB_OBJLOADER_H
#define GRAPHICS_LAB_OBJLOADER_H

#include <vector>

using std::string;
using std::vector;
using namespace glm;

struct face {
    uint32_t v1;
    uint32_t v2;
    uint32_t v3;
    uint32_t n1;
    uint32_t n2;
    uint32_t n3;
};

/*
 * Class for loading .obj file
 */
class ObjLoader {
public:
    explicit ObjLoader(string file);
    vector<fvec3> vertices;
    vector<fvec3> normals;
    vector<face> faces;
};


#endif //GRAPHICS_LAB_OBJLOADER_H
