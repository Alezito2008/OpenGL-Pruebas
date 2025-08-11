#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

void Camera::UpdateVectors()
{
	m_cameraDirection = glm::normalize(m_cameraPos - m_cameraTarget);
	m_cameraRight = glm::normalize(glm::cross(m_worldUp, m_cameraDirection));
	m_cameraUp = glm::normalize(glm::cross(m_cameraDirection, m_cameraRight));
	m_hasToUpdate = false;
}

void Camera::SetTarget(const glm::vec3& target)
{
	m_cameraTarget = target;
	m_hasToUpdate = true;
}

void Camera::SetPosition(const glm::vec3& position)
{
	m_cameraPos = position;
	m_hasToUpdate = true;
}

void Camera::LookAt(const glm::vec3& position)
{
	m_view = glm::lookAt(
		position,
		m_cameraTarget,
		m_worldUp
	);
}

glm::vec3 Camera::GetRight()
{
	if (m_hasToUpdate) UpdateVectors();
	return m_cameraRight;
}

glm::vec3 Camera::GetUp() {
	if (m_hasToUpdate) UpdateVectors();
	return m_cameraUp;
}

glm::mat4 Camera::GetView()
{
	return m_view;
}
