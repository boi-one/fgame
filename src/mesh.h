#pragma once
#include <GL/glew.h>
#include "shader.h"

struct Mesh
{
	unsigned int VBO, VAO, EBO;

	Mesh()
	{
		float vertices[] =
		{
			0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
			0.5f, -0.5f,  	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		   -0.5f, -0.5f,  	0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
		   -0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		};

		unsigned int indices[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
};