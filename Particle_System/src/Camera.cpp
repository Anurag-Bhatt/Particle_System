#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up)
	: m_Position(position), m_Front(front), m_Up(up)
{
}

glm::mat4 Camera::look_at() const
{
	return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

glm::mat4 Camera::look_at(glm::vec3& eye, glm::vec3& center, glm::vec3& up) const
{
	return glm::lookAt(eye, eye + center, up);
}

void Camera::update_position(glm::vec3 distance)
{
	m_Position += distance * camera_speed;
}
