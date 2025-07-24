#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "logger.h"

const char* vertexShaderSourceT = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"void main() {\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSourceT = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int mainT() {
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

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	// Crear variable para guardar id del vertex shader
	unsigned int vertexShader;
	// Se le asigna el id del shader creado y el tipo
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Cargar y compilar el codigo fuente del shader
	glShaderSource(vertexShader, 1, &vertexShaderSourceT, NULL);
	glCompileShader(vertexShader);

	// Variable para guardar el estado de compilación
	int success;
	// String para almacenar información en caso de haber errores
	char infoLog[512];
	// Obtener el estado de compilación y guardarlo en success
	glad_glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		// Si hay errores, guarda el error en infoLog
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error al compilar vertex shader: " << infoLog << std::endl;
	}

	// Crear fragment shader y compilar
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSourceT, NULL);
	glCompileShader(fragmentShader);

	glad_glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Error al compilar fragment shader: " << infoLog << std::endl;
	}

	// ShaderProgram es una combinación de varios shaders
	unsigned int shaderProgram;
	// Se asigna el id del nuevo program a shaderProgram
	shaderProgram = glCreateProgram();
	// Le dice que shaders se van a usar en el program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Termina el enlace
	glLinkProgram(shaderProgram);

	glad_glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Error al linkear shaders: " << infoLog << std::endl;
	}

	// Ya no necesitamos los shaders que creamos así que los eliminamos
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// VAO es donde se pueden guardar configuraciones como el VBO y los attribs que usa
	unsigned int VAO;
	// Le asigna un id al VAO
	glad_glGenVertexArrays(1, &VAO);
	// Comienza la escritura
	glBindVertexArray(VAO);

	// -- 0. Copiar los vertices a un buffer para que lo use OpenGL -- //
	// VBO = Vertex Buffer Object (un contenedor de vertices para la memoria en el GPU), VBO contiene el id del buffer
	unsigned int VBO;
	// Se genera un identificador de buffer
	glad_glGenBuffers(1, &VBO);
	// Se asigna el tipo de buffer (array)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Copia los datos de los vértices al buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// -- 1. Definir los atributos que recibe el shader -- //
	// Le dice al GPU que hay un atributo (es como un argumento que se le pasa a los shaders
	// en la posición 0 (primer arg), que son 3 datos, que es un float, que cada 3 floats es uno de los atributos
	// y empieza desde el primer espacio de memoria
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// -- 2. Decirle a OpenGL que programa usar -- //
	// Usar el shaderProgram, cada llamada nueva que use un shader va a usar este
	glUseProgram(shaderProgram);
	// Comienza a utilizar el VAO
	glBindVertexArray(VAO);
	// Dibujar triángulo
	glDrawArrays(GL_TRIANGLES, 0, 3);



	// Loop principal
	while (!glfwWindowShouldClose(window)) {
		// Procesar teclas
		processInput(window);

		// Especificar color de fondo
		glClearColor(0.0, 0.0, 0.5, 1.0);
		// Limpiar el buffer de fondo y asignarle el color
		glClear(GL_COLOR_BUFFER_BIT);

		// Usar el shaderProgram, cada llamada nueva que use un shader va a usar este
		glUseProgram(shaderProgram);
		// Comienza a utilizar el VAO
		glBindVertexArray(VAO);
		// Dibujar triángulo
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Procesar eventos
		glfwPollEvents();
		// Intercambiar buffer hacia el nuevo
		glfwSwapBuffers(window);
	}

	// Eliminar ventana antes de terminar
	glfwDestroyWindow(window);
	// Terminar OpenGL
	glfwTerminate();


	return 0;
}
