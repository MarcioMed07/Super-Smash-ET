#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "main.h"

void options(SDL_Renderer** renderer, Gamestate *gamestate)
{
	
	
	
	


	
	if(gamestate->gamemode == 0)
	{
		SDL_RenderCopy(*renderer, texture.options0tex,NULL, NULL);
	}

	if(gamestate->gamemode == 1)
	{
		SDL_RenderCopy(*renderer, texture.options1tex,NULL, NULL);
	}


	if(gamestate->optionsroll == 0)
	{
			SDL_Rect optionsrollRect = {1055, 275, 60, 55};
			SDL_RenderCopy(*renderer,texture.menurolltex,NULL ,&optionsrollRect); 
			
	}

	if(gamestate->optionsroll == 1)
	{
			SDL_Rect optionsrollRect = {1055, 370, 60, 55};
			SDL_RenderCopy(*renderer,texture.menurolltex,NULL ,&optionsrollRect); 
			
	}

	if(gamestate->optionsroll == 2)
	{
			SDL_Rect optionsrollRect = {1055, 466, 60, 55};
			SDL_RenderCopy(*renderer,texture.menurolltex,NULL ,&optionsrollRect); 
			
	}

	if(gamestate->optionsroll == 3)
	{
			SDL_Rect optionsrollRect = {1055, 562, 60, 55};
			SDL_RenderCopy(*renderer,texture.menurolltex,NULL ,&optionsrollRect); 
			
	}




	SDL_Rect volumemusicbarRect = {480,290,gamestate->musicvolume*3.7 , 20};
	SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(*renderer, &volumemusicbarRect);

	SDL_Rect volumesoundbarRect = {480,390,gamestate->soundvolume*3.7  , 20};
	SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(*renderer, &volumesoundbarRect);
	
	SDL_RenderPresent(*renderer);
	SDL_RenderClear(*renderer);  

	

}