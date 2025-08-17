#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

void Camera::UpdateVectors()
{
	m_cameraTarget = m_cameraPos + m_cameraFront;
	m_cameraDirection = glm::normalize(m_cameraTarget - m_cameraPos);
	m_cameraRight = glm::normalize(glm::cross(m_cameraDirection, m_worldUp));
	m_cameraUp = glm::normalize(glm::cross(m_cameraDirection, m_cameraRight));
	m_view = glm::lookAt(m_cameraPos, m_cameraTarget, m_cameraUp);
	m_hasToUpdate = false;
}

Camera::Camera()
{
	UpdateVectors();
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

void Camera::SetFront(const glm::vec3& position)
{
	m_cameraFront = position;
	m_hasToUpdate = true;
}

void Camera::Move(const glm::vec3& direction)
{
	m_cameraPos += direction;
	m_hasToUpdate = true;
}

glm::vec3 Camera::GetPosition()
{
	return m_cameraPos;
}

glm::vec3 Camera::GetTarget()
{
	return m_cameraTarget;
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

glm::vec3 Camera::GetFront()
{
	if (m_hasToUpdate) UpdateVectors();
	return m_cameraFront;
}

glm::mat4 Camera::GetView()
{
	if (m_hasToUpdate) UpdateVectors();
	return m_view;
}
