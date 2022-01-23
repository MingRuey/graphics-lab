#ifndef GRAPHICS_LAB_SHADERLOADER_H
#define GRAPHICS_LAB_SHADERLOADER_H

class ShaderLoader {
public:
    ShaderLoader(const std::string &vertexPath, const std::string &fragmentPath);
    void use() const;
    void remove() const;
private:
    unsigned int ID;
};

#endif //GRAPHICS_LAB_SHADERLOADER_H
