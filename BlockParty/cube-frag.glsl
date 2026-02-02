
#version 330

out vec4 FragColor;

uniform vec3 lightColor;
uniform float intensity;

uniform vec3 objColor;

void main()
{
	vec3 ambient = objColor * lightColor * intensity * 0.2f;

	FragColor = vec4(ambient, 1.0f);
}