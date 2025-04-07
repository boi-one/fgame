#include "input.h"
#include "imgui_impl_sdl2.h"

void Input::SDLEvents(SDL_Event& event, bool running)
{
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
		if (event.type == SDL_QUIT)	running = false;
	}
}

void Input::UpdateMouse()
{

}

void Input::UpdateKeyboard()
{

}

void Input::ProcessInput()
{

}

void Input::RegisterInput()
{

}
