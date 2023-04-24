#version 330 core
in vec4 color;
in vec2 texCoord;

layout (location = 0) out vec4 fragColor;

uniform sampler2D tex0;

void main()
{
	fragColor = texture(tex0, texCoord);
	//fragColor = vec4(texCoord, 0.0f, 1.0f);
	//fragColor = color;
}