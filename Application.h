#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowManager.h"
#include "Renderer.h"
#include "InputManager.h"

class Application
{
public:
	Application(const WindowSettings& settings);
	virtual ~Application();
	void Run();

protected:
	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Exit();

	inline const InputManager& GetInputManager() const { return m_inputManager; }
	inline const WindowManager& GetWindowManager() const { return m_windowManager; }
	inline const Renderer& GetRenderer() const { return m_renderer; }

	WindowManager m_windowManager;
	GLFWwindow* m_window;
	Renderer m_renderer;
	InputManager m_inputManager;
};
