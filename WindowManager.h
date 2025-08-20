#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <functional>

struct WindowSettings {
	const std::string name;
	int width;
	int height;
	WindowSettings(const std::string& name, int width, int height)
		: name(name), width(width), height(height) {};
};


enum class CursorMode {
	Normal = GLFW_CURSOR_NORMAL,
	Hidden = GLFW_CURSOR_HIDDEN,
	Disabled = GLFW_CURSOR_DISABLED
};

class WindowManager
{
public:
	WindowManager(const WindowSettings& settings);
	~WindowManager();

	inline GLFWwindow* GetWindow() const { return m_window; };
	const WindowSettings& GetSettings() const;

	using CursorPosCallback = std::function<void(double, double)>;

	void PollEventsAndSwapBuffers();
	void SetDimensions(int width, int height);
	void SetCursorMode(CursorMode mode);
	void SetCursorPosCallback(CursorPosCallback handler);
	void CloseWindow();

	float GetAspectRatio() const;
	bool GetWindowShouldClose() const;
	inline const WindowSettings& GetWindowsSettings() { return m_windowSettings; }
	CursorMode GetCursorMode() const;
private:
	GLFWwindow* m_window;
	WindowSettings m_windowSettings;

	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	static void CursorPosCallbackInternal(GLFWwindow* window, double posX, double posY);

	CursorPosCallback m_cursorPosCallback = nullptr;
};

