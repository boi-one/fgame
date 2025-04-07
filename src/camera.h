#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	struct Viewport
	{
		int windowWidth = 500;
		int windowHeight = 500;

		float left{ 0 }, right{ 0 }, top{ 0 }, bottom{ 0 };
	};
	Viewport viewport;
	glm::vec2 position = glm::vec2(0, 0);

	void SetProjection()
	{
		viewport.left = -(viewport.windowWidth * 0.5f);
		viewport.right = viewport.windowWidth * 0.5f;
		viewport.top = viewport.windowHeight * 0.5f;
		viewport.bottom = -(viewport.windowHeight * 0.5f);

		float scale = 0.01f;

		projection = glm::mat4(1.0f);

		projection = glm::ortho(
			(viewport.left + position.x) * scale,
			(viewport.right + position.x) * scale,
			(viewport.bottom + position.y) * scale,
			(viewport.top + position.y) * scale,
			-1.0f, 1.0f);
	}
	glm::mat4 GetProjection()
	{
		return projection;
	}

	glm::vec2 ToWorldPosition(glm::vec2 input);

private:
	glm::mat4 projection;
};