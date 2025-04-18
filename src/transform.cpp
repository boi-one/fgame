#include "transform.h"

void Transform::SetTransform()
{
	transform = glm::mat4(1);
	transform = glm::scale(transform, glm::vec3(scale, 1.0f));
	transform = glm::rotate(transform, glm::radians(rotation), { 0, 0, 1 });
	transform = glm::translate(transform, glm::vec3(position, 0));
}

glm::mat4 Transform::GetTransform()
{
	return transform;
}
