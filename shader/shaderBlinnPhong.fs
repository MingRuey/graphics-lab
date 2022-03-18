#version 330 core

in vec4 normal;
in vec3 halfVector;
in vec3 lightdir;

out vec4 fragmentColor;

uniform vec3 objectColor;

void main(void)
{
	vec3 n = normalize(normal.xyz);
	vec3 h = normalize(halfVector);
	vec3 l = normalize(lightdir);
	
	vec3 intensity = 0.1 
					+ 1 * objectColor * max( 0.0, dot(n, l) )
					+ 0.3 * objectColor * pow( max( 0.0, dot(n, h) ), 32 );
	fragmentColor = vec4( intensity, 1.0 );

}