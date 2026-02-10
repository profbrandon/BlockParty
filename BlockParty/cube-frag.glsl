
#version 330

in  vec3 fragPos;
in  vec3 aNormal;
out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float intensity;

uniform vec3 objColor;

uniform vec3 viewPos;

void main()
{
	vec3 lightDir = normalize(lightPos - fragPos);
	vec3 viewDir  = normalize(viewPos - fragPos);
	vec3 reflDir  = reflect(-lightDir, aNormal);

	float ambient = intensity * 0.1f;


	float normCos = max(dot(aNormal, normalize(lightPos - fragPos)), 0.0f);
	float diffuse = normCos * intensity;


	float strength = pow(max(dot(viewDir, reflDir), 0.0), 10);
	float specular = 0.5f * strength;


	vec3 lighting = min((ambient + diffuse + specular) * objColor * lightColor, 1.0f);

	FragColor = vec4(lighting, 1.0f);
}