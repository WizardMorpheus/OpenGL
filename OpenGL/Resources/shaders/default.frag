#version 330 core
in vec4 color;
in vec2 texCoord;
in vec3 norm;
in vec3 crntPos;

layout (location = 0) out vec4 fragColor;

uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
	float ambient = 0.2f;
	vec3 normal = normalize(norm);
	vec3 lightDir = normalize(lightPos - crntPos);

	float diffuse = max(dot(normal, lightDir), 0.0f);

	float specularLight = 0.5f;
	vec3 viewDir = normalize(camPos - crntPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 20);
	float specular = specAmount * specularLight;

	fragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
	//fragColor = vec4(texCoord, 0.0f, 1.0f);
	//fragColor = color;
}