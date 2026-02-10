
#version 330

in  vec3 fragPos;
in  vec3 aNormal;
out vec4 FragColor;

uniform vec3 lightColor;
uniform float intensity;

uniform vec3 lightPos;
uniform vec3 objColor;

void main()
{
	vec3 ambient = objColor * lightColor * intensity * 0.1f;

	float normCos = max(dot(aNormal, normalize(lightPos - fragPos)), 0.0f);

	vec3 diffuse = normCos * lightColor * objColor * intensity;

	vec3 lighting = min(ambient + diffuse, 1.0f);

	FragColor = vec4(lighting, 1.0f);
}