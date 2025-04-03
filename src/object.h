#pragma once
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"

class Object
{
public:
	Mesh mesh;
	Texture texture;
	Transform transform;
	Shader shader = Shader("resources/shaders/default.vert", "resources/shaders/default.frag");

	Object()
	{
		std::cout << &shader << std::endl;
	}

	void Render();

};