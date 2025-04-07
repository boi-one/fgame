#pragma once
#include "SDL.h"

class Input
{
	void SDLEvents(SDL_Event& event, bool running);
	void UpdateMouse();
	void UpdateKeyboard();
	void ProcessInput();
	void RegisterInput();
};