#include "mouse.h"


void Mouse::Update(Camera& camera)
{
	position = camera.ToWorldPosition(screenPosition);
	RegisterHold(leftDown, leftHold);
	RegisterHold(rightDown, rightHold);
	RegisterHold(middleDown, middleHold);

}

void Mouse::SetScreenPosition(int x, int y)
{
	position = { x, y };
}

void Mouse::RegisterInput(bool registerDown, bool& mdown, bool& mhold)
{
	if (registerDown) mdown = true;
	else
	{
		mhold = false;
		mdown = false;
	}
}

void Mouse::RegisterHold(bool& mdown, bool& mhold)
{
	if (mdown)
	{
		mdown = false;
		mhold = true;
	}
}

void Mouse::ProcessInput(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:
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

