
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

	vec3 ambient = objColor * lightColor * intensity * 0.1f;


	float normCos = max(dot(aNormal, normalize(lightPos - fragPos)), 0.0f);
	vec3  diffuse = normCos * lightColor * objColor * intensity;


	float strength = pow(max(dot(viewDir, reflDir), 0.0), 10);
	vec3  specular = 0.5f * strength * lightColor;


	vec3 lighting = min(ambient + diffuse + specular, 1.0f);

	FragColor = vec4(lighting, 1.0f);
}