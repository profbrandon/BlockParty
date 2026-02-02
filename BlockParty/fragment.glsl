
#version 330

out vec4 FragColor;

uniform vec3 objColor;

void main()
{
	FragColor = vec4(objColor, 1.0f);
}