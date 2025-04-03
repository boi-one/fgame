#version 330 core

in vec3 Color;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D Tex;

void main()
{
	FragColor = texture(Tex, vec2(TexCoord.x, 1 - TexCoord.y));
}
