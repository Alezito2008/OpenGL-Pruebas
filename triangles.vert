#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vertexColor;

uniform float offsetX;

void main() {
	vec3 newPos = aPos * -1.0f;
	gl_Position = vec4(newPos.x + offsetX, newPos.y, newPos.z, 1.0);
	vertexColor = aColor;
}
