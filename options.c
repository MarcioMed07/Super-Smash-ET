#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "main.h"

void options(SDL_Window** window, SDL_Renderer**renderer)
{
	
	SDL_RenderCopy(*renderer, texture.optionstex,NULL, NULL);
	SDL_SetRenderDrawColor(*renderer, 0, 0,0, 0);

	SDL_RenderPresent(*renderer);
	SDL_RenderClear(*renderer);  

	

}