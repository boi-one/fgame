#include "texture.h"

bool Texture::ImageExists(const char* filePath)
{
	if (FILE* file = fopen("resources/textures/container.png", "r"))
	{
		printf("file found\n");
		fclose(file);
		return true;
	}
	else
	{
		printf("File not found\n");
		return false;
	}
}
