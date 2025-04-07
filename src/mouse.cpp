#include "mouse.h"
#include "SDL.h"

void Mouse::Update(Camera& camera)
{
	position = camera.ToWorldPosition(screenPosition);
	ProcessInput();
}

void Mouse::SetScreenPosition(int x, int y)
{
	position = { x, y };
}

void Mouse::RegisterInput(bool registerDown, bool& down, bool& hold)
{
	if (registerDown)
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

void Mouse::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) //TODO: MOVE THIS ONE TO THE MAIN SDL_EVENTS LOOP
	{
		printf("Event type: %d\n", event.type);

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				printf("down");
				RegisterInput(true, leftDown, leftHold);
				break;
			case SDL_BUTTON_RIGHT:
				RegisterInput(true, rightDown, rightHold);
				break;
			case SDL_BUTTON_MIDDLE:
				RegisterInput(true, middleDown, middleHold);
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				RegisterInput(false, leftDown, leftHold);
				break;
			case SDL_BUTTON_RIGHT:
				RegisterInput(false, rightDown, rightHold);
				break;
			case SDL_BUTTON_MIDDLE:
				RegisterInput(false, middleDown, middleHold);
				break;
			}
			break;
		}
	}
}

bool Mouse::LeftDown()
{
	return leftDown;
}

bool Mouse::LeftHold()
{
	return leftHold;
}

bool Mouse::RightDown()
{
	return rightDown;
}

bool Mouse::RightHold()
{
	return rightHold;
}

bool Mouse::MiddleDown()
{
	return middleDown;
}

bool Mouse::MiddleHold()
{
	return middleHold;
}

