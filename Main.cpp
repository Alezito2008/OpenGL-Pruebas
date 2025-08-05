#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "logger.h"
#include "Shader.h"

#include <stb/stb_image.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {

	glfwInit();

	// Decirle a OpenGL los datos sobre la versión
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Crear ventana de 800x800 llamada "Pruebas"
	GLFWwindow* window = glfwCreateWindow(1000, 1000, "Pruebas", NULL, NULL);
	// Si no se pudo crear, terminar
	if (window == NULL) {
		logger.error("No se pudo crear la ventana");
		glfwTerminate();
		return -1;
	}

	// Asignar el contexto a la ventana
	glfwMakeContextCurrent(window);
	// Handlear cambios de tamaño
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Cargar GLAD
	gladLoadGL();

	// Especificar el viewport
	glViewport(0, 0, 1000, 1000);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// -- Creación de shaders -- //

	int success;
	char infoLog[512];

	Shader shaderTextura = Shader("texture.vert", "texture.frag");

	float vertices[] = {
		-0.5f, -0.5f, /* abajo izquierda */ 0.0f, 0.0f,
		0.5f, -0.5f, /* abajo derecha* */ 1.0f, 0.0f,
		0.5f, 0.5f, /* arriba derecha */ 1.0f, 1.0f,
		-0.5f, 0.5f, /* arriba izquierda */ 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2, // primer triangulo (arriba derecha)
		2, 3, 0, // segundo triangulo (abajo izquierda)
	};

	// -- Parte de las texturas --

	stbi_set_flip_vertically_on_load(true);

	// Repetición
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Filtros
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Importar imagen
	// ---------------

	int img_width, img_height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &img_width, &img_height, &nrChannels, 0);

	// Ahora si se crea la textura

	unsigned int texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Error al cargar textura1" << std::endl;
	}
	stbi_image_free(data);

	// TEXTURA 2
	data = stbi_load("awesomeface.png", &img_width, &img_height, &nrChannels, 0);

	unsigned int texture2;
	glGenTextures(1, &texture2);

	glBindTexture(GL_TEXTURE_2D, texture2);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Error al cargar textura2" << std::endl;
	}

	// -- Las cositas de los vertices --

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.0, 0.0, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		// primer triangulo
		shaderTextura.use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glUniform1i(glGetUniformLocation(shaderTextura.ID, "textura1"), 0);
		glUniform1i(glGetUniformLocation(shaderTextura.ID, "textura2"), 1);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// Eliminar ventana antes de terminar
	glfwDestroyWindow(window);
	// Terminar OpenGL
	glfwTerminate();


	return 0;
}
