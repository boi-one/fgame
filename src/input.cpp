#include "input.h"

void Input::SDLEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
		if (event.type == SDL_QUIT)	running = false;
		mouse.ProcessInput(event);
	}
}

void Input::UpdateMouse()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	mouse.SetScreenPosition(mouseX, mouseY);
	mouse.Update(*camera);
}

void Input::Update(float deltaTime)
{
	SDLEvents();
	UpdateMouse();
	ProcessInput();

	const Uint8* keyState = SDL_GetKeyboardState(nullptr);
	if (keyState[SDL_SCANCODE_F1]) printf("f1");
	if (mouse.LeftDown()) printf("click\n");
}

void Input::ProcessInput()
{
	const Uint8* key = SDL_GetKeyboardState(0);
	for (int i = 0; i < KEYSLENGTH; i++)
	{
		input[i].RegisterInput(key);
	}
}

bool Input::Key::Down() const
{
	return down;
}

bool Input::Key::Hold() const
{
	return hold;
}

/// not implemented yet
bool Input::Key::Up() const
{
	return false;
}

void Input::Key::RegisterInput(const Uint8* key) const
{
	if (key[sdlk])
	{
		if (!hold) down = true;
		else hold = false;
		hold = true;
	}
	else
	{
		hold = false;
		down = false;
	}
}
