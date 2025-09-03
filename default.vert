#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat3 normalMatrix;

struct MVP {
	mat4 model;
	mat4 view;
	mat4 projection;
};

uniform MVP mvp;

void main() {
	gl_Position = mvp.projection * mvp.view * mvp.model * vec4(aPos, 1.0);
	FragPos = vec3(mvp.model * vec4(aPos, 1.0));
	Normal = normalMatrix * aNormal;
}
