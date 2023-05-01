#include "../include/Window.h"

namespace graphic_system_lib
{
	bool Window::init(const char* name, int32_t width, int32_t height,
		GLFWmonitor* monitor, GLFWwindow* share)
	{
		return m_Window = glfwCreateWindow(width, height, name, monitor,
			share);
	}
}
