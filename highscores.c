#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>

void highscores(SDL_Window** window, SDL_Renderer**renderer)
{
	

    SDL_Texture *highscorestex = IMG_LoadTexture(*renderer, "images/menu/highscores.png");
	SDL_RenderCopy(*renderer, highscorestex,NULL, NULL);
	SDL_SetRenderDrawColor(*renderer, 0, 0,0, 0);

	SDL_RenderPresent(*renderer);
	SDL_RenderClear(*renderer);  

	

}