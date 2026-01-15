#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {

public:

	Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up);

	glm::mat4 look_at() const;
	glm::mat4 look_at(glm::vec3& eye, glm::vec3& center, glm::vec3& up) const;
	
	void update_position(glm::vec3 distance);

	float camera_speed = 5.0f;

private:

	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;

};