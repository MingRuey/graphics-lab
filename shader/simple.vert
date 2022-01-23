#version 330 core

layout (location = 0) in vec3 aPos;

void main() {
    mat4 transMat = mat4(1.0, 0.0, 0.0, 0.0,
                         0.0, 1.0, 0.0, 0.0,
                         0.0, 0.0, 1.0, 0.0,
                         0.0, 0.0, 0.0, 1.0);
    gl_Position = transMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
