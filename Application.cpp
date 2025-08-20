#include "Application.h"

Application::Application(const WindowSettings& settings)
	: m_windowManager(settings),
	m_window(m_windowManager.GetWindow()),
	m_renderer(),
	m_inputManager(m_window)
{}

Application::~Application() {}

void Application::Run()
{
	Start();

	float lastTime = static_cast<float>(glfwGetTime());

	while (!m_windowManager.GetWindowShouldClose()) {
		float currentTime = static_cast<float>(glfwGetTime());
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		m_renderer.Clear();

		Update(deltaTime);

		m_windowManager.PollEventsAndSwapBuffers();
	}

	Exit();
}

void Application::Start()
{

}

void Application::Update(float deltaTime)
{

}

void Application::Exit()
{

}
