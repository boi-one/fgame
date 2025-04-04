#pragma once
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Transform
{
	glm::vec2 position = glm::vec2(0, 0);
	glm::vec2 scale = glm::vec2(1, 1);
	/// <summary> rotation in degrees </summary>
	float rotation = 0;

	void SetTransform();

private:
	glm::mat4 transform = glm::mat4(1);
};
