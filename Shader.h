#pragma once

#include <glad/glad.h>

#include <string>
#include <iostream>
#include <glm/matrix.hpp>

class Shader
{
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	void Bind() const;
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, glm::mat4 matrix) const;
};

