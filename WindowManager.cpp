#include "WindowManager.h"

#include <iostream>

void WindowManager::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	WindowManager* wm = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
	if (wm) {
		wm->SetDimensions(width, height);
	}
	glViewport(0, 0, width, height);
}

void WindowManager::CursorPosCallbackInternal(GLFWwindow* window, double posX, double posY)
{
	WindowManager* wm = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
	if (wm && wm->m_cursorPosCallback) {
		wm->m_cursorPosCallback(posX, posY);
	}
}

WindowManager::WindowManager(const WindowSettings& settings) : m_windowSettings(settings)
{

	if (!glfwInit()) {
		std::cout << "Error: No se pudo inicializar GLFW" << std::endl;
		std::exit(-1);
	};

	// Decirle a OpenGL los datos sobre la versión
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Crear ventana
	m_window = glfwCreateWindow(m_windowSettings.width, m_windowSettings.height, m_windowSettings.name.c_str(), NULL, NULL);
	// Si no se pudo crear, terminar
	if (m_window == NULL) {
		std::cout << "Error: No se pudo crear la ventana" << std::endl;
		glfwTerminate();
		std::exit(-1);
	}

	glfwSetWindowUserPointer(m_window, this);
	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Erro al inicializar GLAD" << std::endl;
		std::exit(-1);
	}

	glViewport(0, 0, m_windowSettings.width, m_windowSettings.height);

	// Handlear cambios de tamaño
	glfwSetFramebufferSizeCallback(m_window, FrameBufferSizeCallback);
}

WindowManager::~WindowManager()
{
	// Eliminar ventana antes de terminar
	glfwDestroyWindow(m_window);
	// Terminar OpenGL
	glfwTerminate();
}

const WindowSettings& WindowManager::GetSettings() const
{
	return m_windowSettings;
}

void WindowManager::PollEventsAndSwapBuffers()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void WindowManager::SetDimensions(int width, int height)
{
	m_windowSettings.width = width;
	m_windowSettings.height = height;
	glViewport(0, 0, width, height);
}

void WindowManager::SetCursorMode(CursorMode mode)
{
	glfwSetInputMode(m_window, GLFW_CURSOR, static_cast<int>(mode));
}

void WindowManager::SetCursorPosCallback(CursorPosCallback handler)
{
	m_cursorPosCallback = handler;
	glfwSetCursorPosCallback(m_window, CursorPosCallbackInternal);
}

void WindowManager::CloseWindow()
{
	glfwSetWindowShouldClose(m_window, true);
}

float WindowManager::GetAspectRatio() const
{
	return static_cast<float>(m_windowSettings.width) / m_windowSettings.height;
}

bool WindowManager::GetWindowShouldClose() const
{
	return glfwWindowShouldClose(m_window);
}

CursorMode WindowManager::GetCursorMode() const
{
	int mode = glfwGetInputMode(m_window, GLFW_CURSOR);
	return static_cast<CursorMode>(mode);
}
