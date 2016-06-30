#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "main.h"

void highscores(SDL_Window** window, SDL_Renderer**renderer)
{
	

	SDL_RenderCopy(*renderer, texture.highscorestex,NULL, NULL);
	SDL_SetRenderDrawColor(*renderer, 0, 0,0, 0);

	SDL_RenderPresent(*renderer);
	SDL_RenderClear(*renderer);  

	

}