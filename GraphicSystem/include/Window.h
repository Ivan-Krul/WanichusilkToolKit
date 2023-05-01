#pragma once
#include "Initializer.h"

namespace graphic_system_lib
{
	class Window
	{
	public:
		bool init(const char* name, int32_t width, int32_t height,
			GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);

		inline bool fail()
		{ return !m_Window; }

		inline GLFWwindow* getWindowInstance() noexcept
		{ return m_Window; }

		inline void bindGraphicContext() noexcept
		{
			glfwMakeContextCurrent(m_Window);
			m_IsGraphicContextBinded = true;
		}

		inline bool checkShouldClose() noexcept
		{ return glfwWindowShouldClose(m_Window); }

		inline void swapBuffer()
		{
			if(m_IsGraphicContextBinded)
				glfwSwapBuffers(m_Window);
		}

	private:
		GLFWwindow* m_Window;
		bool m_IsGraphicContextBinded = false;

	};
}
