#pragma once
#include "glm/glm.hpp"
#include "camera.h"

class Mouse
{
public:
	glm::vec2 position = glm::vec2(0);
	glm::vec2 screenPosition = glm::vec2(0); ///the position on your screen (pixel coordinates, top left = 0, 0)

	void Update(Camera& camera);
	void SetScreenPosition(int x, int y);

	void RegisterInput(bool registerDown, bool& down, bool& hold);
	void ProcessInput();
		
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
	bool leftDown;
	bool leftHold;
	bool leftUp;

	bool rightDown;
	bool rightHold;
	bool rightUp;

	bool middleDown;
	bool middleHold;
	bool middleUp;
};