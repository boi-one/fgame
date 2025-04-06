#pragma once
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include <vector>

class Object
{
public:
	static inline std::vector<Object> allObjects;
	Mesh mesh;
	Texture texture;
	Transform transform;
	Shader shader = Shader("resources/shaders/default.vert", "resources/shaders/default.frag");

	Object(glm::vec2 position = glm::vec2(0, 0), glm::vec2 scale = glm::vec2(1, 1), const char* texturePath = DEFAULT_TEXTURE)
	{
		allObjects.emplace_back(*this);
		texture = Texture(texturePath);
		transform = Transform(position, scale);
	}

	void Render();
};