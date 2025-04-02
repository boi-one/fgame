#include "shader.h"

int CheckForLinking(unsigned int program);
int CheckForSuccess(unsigned int shader);

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;
	
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	CheckForSuccess(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	CheckForSuccess(fragmentShader);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	CheckForLinking(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::SetBool(const string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::SetFloat(const string& name, float value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetInt(const string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetVec2(const string& name, glm::vec2 value) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::SetVec3(const string& name, glm::vec3 value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::SetMat2(const std::string& name, const glm::mat2& value) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetMat3(const std::string& name, const glm::mat3& value) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

int CheckForSuccess(unsigned int shader)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		switch (shader)
		{
		case GL_VERTEX_SHADER:
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			break;
		case GL_FRAGMENT_SHADER:
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			break;
		case GL_LINK_STATUS:
			std::cout << "ERROR::LINK::STATUS::COMPILATION_FAILED\n" << infoLog << std::endl;
			break;
		}
		return -1;
	}
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		switch (shader)
		{
		case GL_VERTEX_SHADER:
			std::cout << "VERTEX" << std::endl;
			break;
		case GL_FRAGMENT_SHADER:
			std::cout << "FRAGMENT" << std::endl;
			break;
		case GL_LINK_STATUS:
			std::cout << "LINKING" << std::endl;
			break;
		default:
			std::cout << "other" << std::endl;
			break;
		}
		std::cout << "OpenGL error: " << err << std::endl;
	}
	return success;
}

int CheckForLinking(unsigned int program)
{
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return -1;
	}
	return success;
}
