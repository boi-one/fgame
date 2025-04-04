#include "transform.h"

void Transform::SetTransform()
{
	transform = glm::rotate(transform, glm::radians(rotation), { 0, 0, 1 });
	transform = glm::translate(transform, glm::vec3(position, 0));
	transform = glm::scale(transform, glm::vec3(scale, 0));
}
