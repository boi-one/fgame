#pragma once
#include <GL/glew.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>

#define DEFAULT_TEXTURE "resources/textures/container.png"

struct Texture
{
	unsigned int handle = 0;
	
	Texture(const char* textureFilePath = DEFAULT_TEXTURE)
	{
		if (!ImageExists(textureFilePath))
		{
			handle = 0;
			std::cout << "image does not exist" << std::endl;
			return;
		};

		SDL_Surface* surface = IMG_Load(textureFilePath);
		glGenTextures(1, &handle);
		glBindTexture(GL_TEXTURE_2D, handle);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		SDL_FreeSurface(surface);
	}

private:
	bool ImageExists(const char* filePath);
};