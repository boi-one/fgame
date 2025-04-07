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
	Shader* shader = nullptr;

	Object(Shader* shader, glm::vec2 position = glm::vec2(0, 0), glm::vec2 scale = glm::vec2(1, 1), const char* texturePath = DEFAULT_TEXTURE)
	{
		this->shader = shader;
		allObjects.emplace_back(*this);
		texture = Texture(texturePath);
		transform = Transform(position, scale);
	}

	void Render();
};