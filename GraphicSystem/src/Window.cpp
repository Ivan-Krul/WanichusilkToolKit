#include "../include/Window.h"
#include <stdio.h>

namespace graphic_system_lib
{
	bool Window::create(const char* name, size_t width, size_t height)
	{
		//Create window
		mpWindow = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (mpWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			//Get window surface
			mpScreenSurface = SDL_GetWindowSurface(mpWindow);
		}
		return false;
	}

	void Window::terminate()
	{
		SDL_DestroyWindow(mpWindow);
		mpWindow = NULL;
	}
}
