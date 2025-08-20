#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Application.h"
#include "WindowManager.h"
#include "Shader.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Camera.h"
#include "InputManager.h"
#include "Texture.h"

static float cubeVertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

class Pruebas : public Application {
public:
	Pruebas(const WindowSettings& settings)
		: Application(settings),
		shaderTextura("texture.vert", "texture.frag"),
		containerTexture("container.jpg"),
		faceTexture("awesomeface.png") {}

	Shader shaderTextura;
	Camera camera;
	VertexArray cubeVA;
	Texture containerTexture;
	Texture faceTexture;
	InputManager inputManager = GetInputManager();
	WindowManager wm = GetWindowManager();
	Renderer renderer = GetRenderer();

	float pitch = 0.0f;
	float yaw = 0.0f;
	float lastX;
	float lastY;

	glm::vec3 cubePositions[10] = {
		{0.0f, 0.0f, 0.0f},
		{2.0f, 5.0f, -15.0f},
		{-1.5f, -2.2f, -2.5f},
		{-3.8f, -2.0f, -12.3f},
		{2.4f, -0.4f, -3.5f},
		{-1.7f, 3.0f, -7.5f},
		{1.3f, -2.0f, -2.5f},
		{1.5f, 2.0f, -2.5f},
		{1.5f, 0.2f, -1.5f},
		{-1.3f, 1.0f, -1.5f}
	};

	// Start: se llama una vez al iniciar
	void Start() override {
		WindowSettings windowSettings = wm.GetSettings();
		lastX = windowSettings.width / 2.0f;
		lastY = windowSettings.height / 2.0f;

		wm.SetCursorMode(CursorMode::Disabled);

		shaderTextura = Shader("texture.vert", "texture.frag");
		containerTexture = Texture("container.jpg");
		faceTexture = Texture("awesomeface.png");

		camera.SetPosition(glm::vec3(0.0f, 0.0f, -3.0f));

		// Configurar VAO y VBO
		VertexBuffer cubeVBO(cubeVertices, sizeof(cubeVertices));
		VertexBufferLayout cubeLayout;
		cubeLayout.Push<float>(3, false); // posiciones
		cubeLayout.Push<float>(2, false); // UV
		cubeVA.AddBuffer(cubeVBO, cubeLayout);

		shaderTextura.Bind();
		glUniform1i(glGetUniformLocation(shaderTextura.ID, "textura1"), 0);
		glUniform1i(glGetUniformLocation(shaderTextura.ID, "textura2"), 1);

		containerTexture.Bind();
		faceTexture.Bind(1);

		glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
	}

	// Update: se llama cada frame
	void Update(float deltaTime) override {
		glm::vec3 direction(0.0f);
		const float cameraSpeed = 0.05f;

		if (inputManager.IsKeyPressed(KeyCode::KEY_W)) direction += camera.GetFront();
		if (inputManager.IsKeyPressed(KeyCode::KEY_S)) direction -= camera.GetFront();
		if (inputManager.IsKeyPressed(KeyCode::KEY_A)) direction -= camera.GetRight();
		if (inputManager.IsKeyPressed(KeyCode::KEY_D)) direction += camera.GetRight();

		// Movimiento del mouse
		double xpos, ypos;
		glfwGetCursorPos(wm.GetWindow(), &xpos, &ypos);
		float sensitivity = 0.2f;
		float deltaX = (xpos - lastX) * sensitivity;
		float deltaY = (ypos - lastY) * sensitivity;
		lastX = xpos;
		lastY = ypos;
		yaw += deltaX;
		pitch += deltaY;
		if (pitch > 89.0f) pitch = 89.0f;
		if (pitch < -89.0f) pitch = -89.0f;

		glm::vec3 front;
		front.x = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		camera.SetFront(front);

		if (glm::length(direction) > 0.0f) {
			direction = glm::normalize(direction);
			camera.Move(direction * cameraSpeed);
		}

		// Dibujar cubos
		glm::mat4 projection = glm::perspective(glm::radians(80.0f), wm.GetAspectRatio(), 0.1f, 100.0f);
		for (glm::vec3 pos : cubePositions) {
			float rotation = 45.0f * static_cast<float>(glfwGetTime()) * 0.001f;
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, pos);
			model = glm::rotate(model, glm::radians(rotation + pos.x), glm::vec3(0.3f, 1.0f, 0.0f));
			shaderTextura.setMat4("transform", projection * camera.GetView() * model);
			renderer.Draw(cubeVA, shaderTextura, 36);
		}
	}

	void Exit() override {
		// limpiar recursos si hace falta
	}
};
