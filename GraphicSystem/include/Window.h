#pragma once
#include "SDL.h"

namespace graphic_system_lib
{
	class Window
	{
	public:
		bool create(const char* name, size_t width, size_t height);

		void terminate();

	private:
		SDL_Window* mpWindow = nullptr;
		SDL_Surface* mpScreenSurface = nullptr;
	};
}
