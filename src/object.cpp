#include "object.h"

void Object::Render()
{
	shader.Use();
	glUseProgram(shader.ID);
	glBindTexture(GL_TEXTURE_2D, texture.handle);
	glBindVertexArray(mesh.VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
