#pragma once
#include <GL/glew.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>

struct Texture
{
	unsigned int handle;

	Texture(const char* textureFilePath)
	{
		if (!ImageExists(textureFilePath))
		{
			handle = 0;
			std::cout << "image does not exsist" << std::endl;
			return;
		};

		SDL_Surface* surface = IMG_Load(textureFilePath);
		glGenTextures(1, &handle);
	}

private:
	bool ImageExists(const char* filePath);
};