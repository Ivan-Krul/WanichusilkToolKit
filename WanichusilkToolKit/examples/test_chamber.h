#pragma once
#pragma comment(lib, "opengl32.lib")
#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

int glew_starter_pack(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "GLEW module with me", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialising was failed!\n");
		glfwTerminate();
		return -1;
	}

	printf("OpenGL version: %s\n", glGetString(GL_VERSION));

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
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
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

int beginner_starter_pack(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glewInit();

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "glew module with me", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
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
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
