
#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;

out vec3 fragPos;
out vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position = proj * view * model * vec4(pos, 1.0f);
	
	fragPos = vec3(model * vec4(pos, 1.0f));
	aNormal = normal;
}