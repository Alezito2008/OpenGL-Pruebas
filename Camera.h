#pragma once

#include <glm/glm.hpp>

class Camera {
private:
	glm::vec3 m_cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_cameraDirection;
	glm::vec3 m_cameraRight;
	glm::vec3 m_cameraUp;
	glm::vec3 m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 m_view;

	bool m_hasToUpdate = true;

	void UpdateVectors();
public:
	Camera();
	void SetTarget(const glm::vec3& target);
	void SetPosition(const glm::vec3& position);
	glm::vec3 GetRight();
	glm::vec3 GetUp();
	glm::mat4 GetView();
};