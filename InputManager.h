#pragma once

#include <GLFW/glfw3.h>

#include "KeyCodes.h"

class InputManager {
private:
	GLFWwindow* m_window;

	inline int KeyToGLFW(KeyCode key) const {
		return static_cast<int>(key);
	}
public:
	InputManager(GLFWwindow* window) :
		m_window(window) {};

	inline bool IsKeyPressed(KeyCode key) const {
		return glfwGetKey(m_window, KeyToGLFW(key)) == GLFW_PRESS;
	};

	inline bool IsKeyReleased(KeyCode key) const {
		return glfwGetKey(m_window, KeyToGLFW(key)) == GLFW_PRESS;
	}
};
