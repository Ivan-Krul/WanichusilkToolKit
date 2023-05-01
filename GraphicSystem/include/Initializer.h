#pragma once
#pragma comment(lib, "opengl32.lib")
#include <GLFW/glfw3.h>

namespace graphic_system_lib
{
	class Initializer
	{
	public:
		inline static Initializer& getInstance() noexcept { return m_Instance; }
		inline constexpr int getResult() const { return m_Result; }

		static int init(bool close_instantly);

	private:
		Initializer() = default;
		~Initializer() { glfwTerminate(); };

		int m_Result;

		static Initializer m_Instance;
	};
}
