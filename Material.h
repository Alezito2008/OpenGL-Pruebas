#pragma once

#include <glm/glm.hpp>

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

// Son materiales de ejemplo que van a venir con el Engine
namespace DefaultMaterial {
	const Material TEST{
		glm::vec3(0.1f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		0.5f
	};
	const Material EMERALD{
		glm::vec3(0.0215f, 0.1745f, 0.0215f),
		glm::vec3(0.07568f, 0.61424f, 0.07568f),
		glm::vec3(0.633f, 0.727811f, 0.633f),
		0.6f
	};
	const Material CYAN_PLASTIC{
		glm::vec3(0.0f, 0.1f, 0.06f),
		glm::vec3(0.0f, 0.50980392f, 0.50980392f),
		glm::vec3(0.50196078f, 0.50196078f, 0.50196078f),
		0.25f
	};
	const Material RED_RUBBER{
		glm::vec3(0.05f, 0.0f, 0.0f),
		glm::vec3(0.5f, 0.4f, 0.4f),
		glm::vec3(0.7f, 0.04f, 0.04f),
		0.078125f
	};
};
