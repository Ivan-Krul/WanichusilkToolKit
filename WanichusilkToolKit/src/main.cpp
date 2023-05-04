#include <SDL.h>
#undef main
#include <stdio.h>

//Starts up SDL and creates window
bool init(const char* name, int screen_width, int screen_height);

//Loads media
bool loadMedia(const char* path);

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

int main(void)
{


	if (!init("Hello SDL", 640, 480))
	{
		printf("SDL didn't initialized\n");
		return 1;
	}

	if (!loadMedia("../resource/hello.png"))
	{
		printf("Failed to load media!\n");
	}

	//Apply the image
	SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

	//Update the surface
	SDL_UpdateWindowSurface(gWindow);

	SDL_Event e;
	bool quit = false;
	while (quit == false)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}

	close();
	return 0;
}

bool init(const char* name,int screen_width, int screen_height)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

bool loadMedia(const char* path)
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gHelloWorld = SDL_LoadBMP(path);
	if (gHelloWorld == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
		success = false;
	}

	return success;
}
void close()
{
	//Deallocate surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
