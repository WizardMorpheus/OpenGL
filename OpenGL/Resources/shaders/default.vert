#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNorm;

out vec4 color;
out vec2 texCoord;
out vec3 norm;
out vec3 crntPos;

uniform mat4 camMat;
uniform mat4 model;

void main()
{
	gl_Position = camMat * vec4(aPos, 1.0f);
	color = vec4(aColor, 1.0f);
	texCoord = aTex;
	norm = aNorm;
	crntPos = vec3(model * vec4(aPos, 1.0f));
}