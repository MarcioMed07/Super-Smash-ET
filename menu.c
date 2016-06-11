#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>

void menu(SDL_Window** window, SDL_Renderer**renderer)
{
	

    SDL_Texture *menutex = IMG_LoadTexture(*renderer, "images/menu/menu.png");
	SDL_RenderCopy(*renderer, menutex,NULL, NULL);
	SDL_SetRenderDrawColor(*renderer, 0, 0,0, 0);

	SDL_RenderPresent(*renderer);
	SDL_RenderClear(*renderer);  

	

}