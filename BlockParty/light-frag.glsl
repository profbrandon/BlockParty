
#version 330

out vec4 FragColor;

uniform vec3 lightColor;
uniform float intensity;

void main()
{
	FragColor = vec4(lightColor * intensity, 0.9f);
}