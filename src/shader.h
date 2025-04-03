#pragma once
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
using std::string;

struct Shader
{
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragmentPath);
	void Use();
	void SetBool(const string& name, bool value) const;
	void SetFloat(const string& name, float value) const;
	void SetInt(const string& name, int value) const;
	void SetVec2(const string& name, glm::vec2 value) const;
	void SetVec3(const string& name, glm::vec3 value) const;
	void SetMat2(const string& name, const glm::mat2& value) const;
	void SetMat3(const string& name, const glm::mat3& value) const;
	void SetMat4(const string& name, const glm::mat4& value) const;
};