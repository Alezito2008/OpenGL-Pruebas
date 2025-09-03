#pragma once

#include <glad/glad.h>

#include <string>
#include <iostream>
#include <glm/matrix.hpp>
#include <unordered_map>

class Shader
{
public:
	unsigned int ID;
	mutable std::unordered_map<std::string, unsigned int> m_LocationCache;
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	void Bind() const;
	unsigned int GetUniformLocation(const std::string& name) const;
	void SetNormalMatrix(const glm::mat4& model);
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setMat3(const std::string& name, const glm::mat3& value) const;
	void setMat4(const std::string& name, const glm::mat4& value) const;
	void setMVP(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const;
};

