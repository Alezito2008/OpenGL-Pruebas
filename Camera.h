#pragma once

#include <glm/glm.hpp>

class Camera {
private:
	glm::vec3 m_cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_cameraDirection;
	glm::vec3 m_cameraRight;
	glm::vec3 m_cameraUp;
	glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 m_view;

	bool m_hasToUpdate = true;

public:
	Camera();
	void UpdateVectors();
	void SetTarget(const glm::vec3& target);
	void SetPosition(const glm::vec3& position);
	void SetFront(const glm::vec3& position);
	void Move(const glm::vec3& offset);
	glm::vec3 GetPosition();
	glm::vec3 GetTarget();
	glm::vec3 GetRight();
	glm::vec3 GetUp();
	glm::vec3 GetFront();
	glm::mat4 GetView();
};