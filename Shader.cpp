#include "Shader.h"

#include "Debug.h"

#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
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
	catch (std::ifstream::failure e) {
		std::cout << "ERROR: No se pudo leer el archivo del shader" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "Error al compilar vertex shader: " << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "Error al compilar fragment shader: " << infoLog << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "Error al linkear shaders: " << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

void Shader::Bind() const {
	glUseProgram(ID);
}

unsigned int Shader::GetUniformLocation(const std::string& name) const
{
	auto location = m_LocationCache.find(name);

	// si no lo encuentra
	if (location == m_LocationCache.end()) {
		unsigned int loc = glGetUniformLocation(ID, name.c_str());
		m_LocationCache[name] = loc;
		return loc;
	}

	return location->second;
}

void Shader::SetNormalMatrix(const glm::mat4& model)
{
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
	setMat3("normalMatrix", normalMatrix);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(GetUniformLocation(name), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setMat3(const std::string& name, const glm::mat3& value) const
{
	glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) const
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setMVP(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const
{
	setMat4("mvp.model", model);
	setMat4("mvp.view", view);
	setMat4("mvp.projection", projection);
}
