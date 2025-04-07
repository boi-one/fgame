#include "camera.h"

glm::vec2 Camera::ToWorldPosition(glm::vec2 input)
{
	glm::vec2 output;

	// to clip space (0, 1)
	output.x = input.x / viewport.windowWidth;
	output.y = input.y / viewport.windowHeight;

	// to NDC (-1, 1)
	output.x = (output.x - 0.5f) * 2;
	output.y = (output.y - 0.5f) * 2;

	// to world space
	output.x = output.x * viewport.windowWidth / 2;
	output.y = output.y * viewport.windowHeight / 2;

	return output += this->position;
}
