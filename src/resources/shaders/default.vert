#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTexCoord;

out vec3 Color;
out vec2 TexCoord;

uniform mat4 Transform;
uniform mat4 Projection;

void main()
{
	gl_Position = Projection * Transform * vec4(aPos, 1.0, 1.0);
	Color = aCol;
	TexCoord = aTexCoord;
}