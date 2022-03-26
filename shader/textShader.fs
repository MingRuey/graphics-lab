#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D tex;
uniform vec3 textColor;

void main() {
	vec4 sample = vec4(1.0,1.0,1.0,texture(tex, TexCoords).r);
    FragColor = vec4(textColor, 1.0); //* tex;
}
