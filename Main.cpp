#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "WindowManager.h"
#include "Shader.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Camera.h"
#include "InputManager.h"
#include "Texture.h"
#include "MeshData.h"

WindowSettings windowSettings("OpenGL", 1500, 1000);

WindowManager windowManager(windowSettings);
GLFWwindow* window = windowManager.GetWindow();

float pitch = 0.0f;
float yaw = 0.0f;

float lastX = windowSettings.width / 2;
float lastY = windowSettings.height / 2;

static void processMouse(double xpos, double ypos) {
	const float sensitivity = 0.2f;

	float deltaX = (xpos - lastX) * sensitivity;
	float deltaY = (ypos - lastY) * sensitivity;

	lastX = xpos;
	lastY = ypos;

	yaw += deltaX;
	pitch += deltaY;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	else if (pitch < -89.0f) {
		pitch = -89.0f;
	}
}

static void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);

	// ###########
	// # SHADERS #
	// ###########

	Shader shaderTextura("texture.vert", "texture.frag");
	Shader shaderDefault("default.vert", "default.frag");


	Texture containerTexture("container.jpg");
	Texture faceTexture("awesomeface.png");

	Renderer renderer;
	Camera camera;
	InputManager inputManager(window);

	// ##########
	// # MESHES #
	// ##########

	// Cubo container
	VertexArray cubeVA;
	VertexBuffer cubeVBO(MeshData::cubeVertices, sizeof(MeshData::cubeVertices));
	VertexBufferLayout cubeLayout;
	cubeLayout.Push<float>(3, false); // posiciones
	cubeLayout.Push<float>(2, false); // UV
	cubeVA.AddBuffer(cubeVBO, cubeLayout);

	shaderTextura.Bind();

	glUniform1i(glGetUniformLocation(shaderTextura.ID, "textura1"), 0);
	glUniform1i(glGetUniformLocation(shaderTextura.ID, "textura2"), 1);

	containerTexture.Bind();
	faceTexture.Bind(1);

	// Light Source
	VertexArray lightVA;
	VertexBuffer lightVBO(MeshData::cubeVertices, sizeof(MeshData::cubeVertices));
	VertexBufferLayout lightLayout;
	lightLayout.Push<float>(3, false); // posiciones
	lightLayout.Push<float>(2, false); // UV (no lo voy a usar para esto)
	lightVA.AddBuffer(lightVBO, lightLayout);

	glClearColor(0.0, 0.0, 0.5, 1.0);

	windowManager.SetCursorMode(CursorMode::Disabled);
	windowManager.SetCursorPosCallback(processMouse);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(80.0f), windowManager.GetAspectRatio(), 0.1f, 100.0f);

	camera.SetPosition(glm::vec3(0.0f, 0.0f, -3.0f));

	// ###############
	// # ILUMINACION #
	// ###############

	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	glm::vec3 cubeColor(1.0f, 0.5f, 0.31f);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		renderer.Clear();

		glm::vec3 direction(0.0f);

		const float cameraSpeed = 0.05f;
		if (inputManager.IsKeyPressed(KeyCode::KEY_W)) {
			direction += camera.GetFront();
		}
		if (inputManager.IsKeyPressed(KeyCode::KEY_S)) {
			direction -= camera.GetFront();
		}
		if (inputManager.IsKeyPressed(KeyCode::KEY_A)) {
			direction += camera.GetRight();
		}
		if (inputManager.IsKeyPressed(KeyCode::KEY_D)) {
			direction -= camera.GetRight();
		}

		glm::vec3 front;
		front.x = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		camera.SetFront(front);

		if (glm::length(direction) > 0.0f) {
			direction = glm::normalize(direction);
			camera.Move(direction * cameraSpeed);
		}

		for (glm::vec3 pos : MeshData::cubePositions) {
			float rotation = 45.0f * static_cast<float>(glfwGetTime()) * 0.001f;

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, pos);
			model = glm::rotate(model, glm::degrees(rotation + pos.x), glm::vec3(0.3f, 1.0f, 0.0f));

			shaderTextura.setMat4("transform", (projection * camera.GetView() * model));

			renderer.Draw(cubeVA, shaderTextura, 36);
		}

		glm::mat4 lightTransform(-1.0);
		lightTransform = glm::translate(lightTransform, glm::vec3(1.0f));
		lightTransform = glm::scale(lightTransform, glm::vec3(0.5f));
		shaderDefault.setMat4("transform", (projection * camera.GetView() * lightTransform));
		renderer.Draw(lightVA, shaderDefault, 36);

		windowManager.PollEventsAndSwapBuffers();
	}


	return 0;
}
