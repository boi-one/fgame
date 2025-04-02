#pragma once
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ftypes.h"
using namespace ftypes;
using std::string;

class Shader
{
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragmentPath);
	void Use();
	void SetBool(const string& name, bool value) const;
	void SetFloat(const string& name, float value) const;
	void SetInt(const string& name, int value) const;
	void SetVec2(const string& name, Vector2 value) const;
	void SetMat4(const string& name, Matrix4x4 value) const;
};