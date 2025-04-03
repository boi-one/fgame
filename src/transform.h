#pragma once
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Transform
{
	glm::vec2 position;
	glm::vec2 scale;
	/// <summary> rotation in degrees </summary>
	float rotation;

	void SetTransform();

private:
	glm::mat4 transform = glm::mat4(1);
};
