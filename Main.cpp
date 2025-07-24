#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "logger.h"

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 vertexColor;"
"void main() {\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   vertexColor = aColor;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 miColor;\n"
"void main() {\n"
"	FragColor = miColor;\n"
"}\0";

const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 vertexColor;"
"void main() {\n"
"	FragColor = vec4(vertexColor, 1.0);\n"
"}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void checkShaderCompileErrors(const unsigned int shader, const char* shaderType) {
	int success;
	char infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Error compilando shader del tipo " << shaderType << ": " << infoLog << std::endl;
	}
}

int main() {

	glfwInit();

	// Decirle a OpenGL los datos sobre la versión
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Crear ventana de 800x800 llamada "Pruebas"
	GLFWwindow* window = glfwCreateWindow(800, 800, "Pruebas", NULL, NULL);
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
	glViewport(0, 0, 800, 800);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// -- Creación de shaders -- //

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	checkShaderCompileErrors(vertexShader, "vertex");

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	checkShaderCompileErrors(fragmentShader, "fragment");

	unsigned int fragmentShader2;
	fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);

	checkShaderCompileErrors(fragmentShader2, "fragment 2");

	unsigned int shaderProgram1;
	shaderProgram1 = glCreateProgram();
	glAttachShader(shaderProgram1, vertexShader);
	glAttachShader(shaderProgram1, fragmentShader);
	glLinkProgram(shaderProgram1);

	unsigned int shaderProgram2;
	shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);

	int success;
	char infoLog[512];

	glad_glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);
		std::cout << "Error al linkear shaders: " << infoLog << std::endl;
	}

	glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
		std::cout << "Error al linkear para shaderProgram2 " << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float firstTriangle[] = {
		// primer triangulo
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
	};

	float secondTriangle[] = {
		// segundo triangulo
		-0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.6f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.4f, -0.3f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	unsigned int VAOs[2], VBOs[2];

	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);


	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.0, 0.0, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		// primer triangulo
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue * 2.0f) / 2.0f) + 0.5f;
		int miColorLocation = glGetUniformLocation(shaderProgram1, "miColor");

		glUseProgram(shaderProgram1);
		glUniform4f(miColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// segundo triangulo
		glUseProgram(shaderProgram2);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// Eliminar ventana antes de terminar
	glfwDestroyWindow(window);
	// Terminar OpenGL
	glfwTerminate();

	
	return 0;
}
