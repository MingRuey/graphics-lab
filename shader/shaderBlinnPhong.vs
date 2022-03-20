#version 330 core
layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;

out vec4 normal;
out vec3 halfVector;
out vec3 lightdir;

uniform vec3 lightPosition;
uniform vec3 viewPosition;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;

void main()
{
	// Calculate lighting in eye space: transform the local
	// position to world and then camera coordinate.
	vec4 pos = modelMatrix * vec4(in_Position, 1.0);
	
	normal = modelMatrix * vec4(in_Normal, 0.0);
	vec3 v = normalize(viewPosition - pos.xyz);
	lightdir = normalize(lightPosition - pos.xyz);
	halfVector = normalize(v + lightdir);
	
	gl_Position = projMatrix * viewMatrix * pos;
}