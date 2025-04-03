#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTexCoord;

out vec3 Color;
out vec2 TexCoord;

uniform mat4 Transform;

void main()
{
	gl_Position = Transform * vec4(aPos.x, aPos.y, 1.0, 1.0);
	Color = aCol;
	TexCoord = aTexCoord;
}