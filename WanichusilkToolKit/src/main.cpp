#include "Initializer.h"
#include "Window.h"

int main(void)
{
	graphic_system_lib::Window window;

	/* Initialize the library */
	graphic_system_lib::Initializer& i = graphic_system_lib::Initializer::getInstance();
	i.init(true);

	/* Create a windowed mode window and its OpenGL context */
	window.init("first window", 640, 480);
	if (window.fail())
		return -1;

	/* Make the window's context current */
	window.bindGraphicContext();

	/* Loop until the user closes the window */
	while (!window.checkShouldClose())
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		
		glClearColor(1, 0, 1, 1);
		
		glBegin(GL_TRIANGLES);
		glColor3ub(122, 122, 240);
		glVertex2f(1.0f, 0.0f);
		glVertex2f(0.0f, 1.0f);
		glVertex2f(0.0f, 0.0f);
		glEnd();
		
		/* Swap front and back buffers */
		window.swapBuffer();

		/* Poll for and process events */
		glfwPollEvents();
	}

	return 0;
}