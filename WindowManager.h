#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

struct WindowSettings {
	const std::string name;
	int width;
	int height;
	WindowSettings(const std::string& name, int width, int height)
		: name(name), width(width), height(height) {};
};

class WindowManager
{
private:
	GLFWwindow* m_window;
	WindowSettings m_windowSettings;

	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
public:
	WindowManager(const WindowSettings& settings);
	~WindowManager();

	GLFWwindow* GetWindow() const;
	const WindowSettings& GetSettings() const;

	void PollEventsAndSwapBuffers();
	void SetDimensions(int width, int height);
	float GetAspectRatio() const;
};

