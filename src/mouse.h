#pragma once
#include "glm/glm.hpp"
#include "camera.h"
#include "SDL.h"

class Mouse
{
public:
	glm::vec2 position = glm::vec2(0);
	glm::vec2 screenPosition = glm::vec2(0); ///the position on your screen (pixel coordinates, top left = 0, 0)

	void Update(Camera& camera);
	void SetScreenPosition(int x, int y);

	void RegisterInput(bool registerDown, bool& mdown, bool& mhold);
	void RegisterHold(bool& mdown, bool& mhold);
	void ProcessInput(SDL_Event& event);
		
	//TODO: make up functionality

	bool LeftDown();
	bool LeftHold();
	//leftup

	bool RightDown();
	bool RightHold();
	//rightup

	bool MiddleDown();
	bool MiddleHold();
	//middleup

private:
	bool leftDown = false;
	bool leftHold = false;
	bool leftUp = false;

	bool rightDown = false;
	bool rightHold = false;
	bool rightUp = false;

	bool middleDown = false;
	bool middleHold = false;
	bool middleUp = false;
};