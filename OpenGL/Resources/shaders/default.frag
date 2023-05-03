#version 330 core
in vec4 color;
in vec2 texCoord;
in vec3 norm;
in vec3 crntPos;

layout (location = 0) out vec4 fragColor;

uniform sampler2D tex0;
uniform sampler2D tex1;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;


vec4 pointLight()
{
	vec3 lightVec = lightPos - crntPos;
	float dist = length(lightVec);
	float a = 1.0;
	float b = 0.1;
	float intensity = 1.0f / (a*dist*dist + b*dist + 1.0f);

	
	float ambient = 0.2f;
	vec3 normal = normalize(norm);
	vec3 lightDir = normalize(lightVec);

	float diffuse = max(dot(normal, lightDir), 0.0f);

	float specularLight = 0.5f;
	vec3 viewDir = normalize(camPos - crntPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 10);
	float specular = specAmount * specularLight;
	
	return (texture(tex0, texCoord) * (diffuse * intensity + ambient) + texture(tex1, texCoord).r * specular * intensity)* lightColor;
}


vec4 directLight()
{
	float ambient = 0.2f;
	vec3 normal = normalize(norm);
	vec3 lightDir = normalize(vec3(1.0f,1.0f, 0.0f));

	float diffuse = max(dot(normal, lightDir), 0.0f);

	float specularLight = 0.5f;
	vec3 viewDir = normalize(camPos - crntPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 10);
	float specular = specAmount * specularLight;
	
	return (texture(tex0, texCoord) * (diffuse + ambient) + texture(tex1, texCoord).r * specular )* lightColor;
}


vec4 spotLight()
{
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	float ambient = 0.2f;
	vec3 normal = normalize(norm);
	vec3 lightDir = normalize(lightPos - crntPos);

	float diffuse = max(dot(normal, lightDir), 0.0f);

	float specularLight = 0.5f;
	vec3 viewDir = normalize(camPos - crntPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 10);
	float specular = specAmount * specularLight;

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDir);
	float intensity = clamp( (angle-outerCone)/(innerCone-outerCone), 0.0f, 1.0f); 
	
	return (texture(tex0, texCoord) * (diffuse * intensity + ambient) + texture(tex1, texCoord).r * specular * intensity)* lightColor;
}


void main()
{
	fragColor = pointLight();
	//fragColor = texture(tex1, texCoord) * lightColor * (diffuse + ambient + specular);

	//fragColor = vec4(texCoord, 0.0f, 1.0f);
	//fragColor = color;
}