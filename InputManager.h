#pragma once

#include <GLFW/glfw3.h>

#include "KeyCodes.h"

class InputManager {
private:
	GLFWwindow* m_window;

	inline int KeyToGLFW(Key key) const {
		return static_cast<int>(key);
	}
public:
	InputManager(GLFWwindow* window) :
		m_window(window) {};

	inline bool IsKeyPressed(Key key) const {
		return glfwGetKey(m_window, KeyToGLFW(key)) == GLFW_PRESS;
	};

	inline bool IsKeyReleased(Key key) const {
		return glfwGetKey(m_window, KeyToGLFW(key)) == GLFW_PRESS;
	}
};
