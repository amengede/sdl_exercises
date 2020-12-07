/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <iostream>

//-------------------------Routine Prototypes----------------//

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface(std::string path);

//-------------------------Constants-----------------------//

//Screen dimension constants
const int SCREEN_WIDTH{ 640 };
const int SCREEN_HEIGHT{ 480 };

//The window we'll be rendering to
SDL_Window* window{ NULL };

//The surface contained by the window
SDL_Surface* screenSurface{ NULL };

//Keypress surfaces
enum KeyPressSurfaces {
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

//holds set of surfaces
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

//current displayed image
SDL_Surface* gCurrentSurface{ NULL };

SDL_Surface* gBackgroundSurface{ NULL };

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

	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("press.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		printf("Failed to load default image!\n");
		success = false;
	}

	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}

	gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		printf("Failed to load down image!\n");
		success = false;
	}

	gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		printf("Failed to load left image!\n");
		success = false;
	}

	gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
	{
		printf("Failed to load right image!\n");
		success = false;
	}

	gBackgroundSurface = loadSurface("stretch.bmp");
	if (gBackgroundSurface == NULL)
	{
		printf("Failed to load right image!\n");
		success = false;
	}

	return success;

}

SDL_Surface* loadSurface(std::string path) {

	SDL_Surface* optimisedSurface{ NULL };

	SDL_Surface* loadedSurface{ SDL_LoadBMP(path.c_str()) };

	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else {
		optimisedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);
		if (optimisedSurface == NULL) {
			printf("Unable to optimise image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}

	return optimisedSurface;
}

void close() {

	gCurrentSurface = NULL;

	for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
		SDL_FreeSurface(gKeyPressSurfaces[i]);
		gKeyPressSurfaces[i] = NULL;
	}

	SDL_FreeSurface(gBackgroundSurface);
	gBackgroundSurface = NULL;

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

			SDL_Rect stretchRect;
			stretchRect.x = 0;
			stretchRect.y = 0;
			stretchRect.w = SCREEN_WIDTH;
			stretchRect.h = SCREEN_HEIGHT;

			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

			while (running) {
				//events
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						running = false;
					}
					else if (e.type == SDL_KEYDOWN) {
						switch (e.key.keysym.sym) {
							case SDLK_UP:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
								break;

							case SDLK_DOWN:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
								break;

							case SDLK_LEFT:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
								break;

							case SDLK_RIGHT:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
								break;

							default:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
								break;
						}
					}
				}

				//graphics
				SDL_BlitScaled(gBackgroundSurface, NULL, screenSurface, &stretchRect);
				SDL_BlitSurface(gCurrentSurface, NULL, screenSurface, NULL);
				SDL_BlitScaled(gBackgroundSurface, NULL, screenSurface, &stretchRect);
				//Update the surface
				SDL_UpdateWindowSurface(window);
			}
		}
	}

	close();
	return 0;
}