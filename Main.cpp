#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "logger.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
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

	// Especificar color de fondo
	glClearColor(0.0, 0.0, 0.5, 1.0);
	// Limpiar el buffer de fondo y asignarle el color
	glClear(GL_COLOR_BUFFER_BIT);
	// Intercambiar buffer hacia el nuevo
	glfwSwapBuffers(window);

	// Loop principal
	while (!glfwWindowShouldClose(window)) {
		// Procesar eventos
		glfwPollEvents();
	}

	// Eliminar ventana antes de terminar
	glfwDestroyWindow(window);
	// Terminar OpenGL
	glfwTerminate();

	
	return 0;
}
