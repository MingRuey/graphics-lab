#ifndef GRAPHICS_LAB_SHADERLOADER_H
#define GRAPHICS_LAB_SHADERLOADER_H

class ShaderLoader {
public:
    ShaderLoader(const std::string &vertexPath, const std::string &fragmentPath);
    void use() const;
    void remove() const;
    void setVec3(const std::string& name, float* value) const;
    void setMat4(const std::string& name, float* value) const;
private:
    unsigned int ID;
};

#endif //GRAPHICS_LAB_SHADERLOADER_H
