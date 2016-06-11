#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>

void options(SDL_Window** window, SDL_Renderer**renderer)
{
	

    SDL_Texture *optionstex = IMG_LoadTexture(*renderer, "images/menu/options.png");
	SDL_RenderCopy(*renderer, optionstex,NULL, NULL);
	SDL_SetRenderDrawColor(*renderer, 0, 0,0, 0);

	SDL_RenderPresent(*renderer);
	SDL_RenderClear(*renderer);  

	

}