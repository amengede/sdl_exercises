/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//-------------------------Routine Prototypes----------------//

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//-------------------------Constants-----------------------//

//Screen dimension constants
const int SCREEN_WIDTH{ 640 };
const int SCREEN_HEIGHT{ 480 };

//The window we'll be rendering to
SDL_Window* window{ NULL };

//The surface contained by the window
SDL_Surface* screenSurface{ NULL };

//For image
SDL_Surface* gHelloWorld{ NULL };

//-------------------------Routine Definitions------------//

bool init() {
	bool success{ true };

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialise! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			screenSurface = SDL_GetWindowSurface(window);
		}
	}

	return success;

}

bool loadMedia() {

	bool success{ true };

	gHelloWorld = SDL_LoadBMP("hello.bmp");

	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}

	return success;

}

void close() {

	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

int main( int argc, char* args[] ) {
	//Initialize SDL
	if( !init() ) {
		printf( "SDL could not initialize!");
	}
	else
	{
		if(!loadMedia()){
			printf( "Failed to load media!");
		}
		else
		{
			bool running{ true };

			SDL_Event e{ NULL };

			while (running) {
				//events
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						running = false;
					}
				}

				//graphics
				SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0x00));

				SDL_BlitSurface(gHelloWorld, NULL, screenSurface, NULL);

				//Update the surface
				SDL_UpdateWindowSurface(window);
			}
		}
	}

	close();
	return 0;
}