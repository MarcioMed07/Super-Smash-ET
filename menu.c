#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "main.h"



void fadeinmenu(SDL_Window** window, SDL_Renderer**renderer)
{
	int opacidade = 0;
	SDL_SetRenderDrawColor(*renderer, 0, 0,0, 0);
	


	while(opacidade < 255)
	{

		SDL_SetTextureBlendMode(texture.menutex,SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(texture.menutex,opacidade);
		SDL_RenderCopy(*renderer, texture.menutex,NULL, 0);
		SDL_SetRenderDrawColor(*renderer, 0, 0,0, 0);


		opacidade += 1;	
		SDL_RenderPresent(*renderer);
		SDL_RenderClear(*renderer);  
	}

																																																																																																																																																																																																																																																																																																																																								

}

void fadeoutmenu(SDL_Window** window, SDL_Renderer**renderer)
{
	int opacidade = 255;
	SDL_SetRenderDrawColor(*renderer, 0, 0,0, 0);
	


	while(opacidade > 0)
	{

		SDL_SetTextureBlendMode(texture.menutex,SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(texture.menutex,opacidade);
		SDL_RenderCopy(*renderer, texture.menutex,NULL, 0);
		SDL_SetRenderDrawColor(*renderer, 0, 0,0, 0);


		opacidade -= 1;	
		SDL_RenderPresent(*renderer);
		SDL_RenderClear(*renderer);  
	}
}

void desenhamenu(SDL_Renderer** renderer, Gamestate *gamestate)
{
	

	SDL_RenderCopy(*renderer, texture.menutex,NULL, 0);
	
	
	

	if(gamestate->menuroll == 0)
	{
			SDL_Rect menuroll0Rect = {1055, 330, 60, 55};
			SDL_RenderCopy(*renderer,texture.menurolltex,NULL ,&menuroll0Rect); 
			
	}

	if(gamestate->menuroll == 1)
	{
			SDL_Rect menuroll0Rect = {1055, 405, 60, 55};
			SDL_RenderCopy(*renderer,texture.menurolltex,NULL ,&menuroll0Rect); 
			
	}

	if(gamestate->menuroll == 2)
	{
			SDL_Rect menuroll0Rect = {1055, 480, 60, 55};
			SDL_RenderCopy(*renderer,texture.menurolltex,NULL ,&menuroll0Rect); 
			
	}

	if(gamestate->menuroll == 3)
	{
			SDL_Rect menuroll0Rect = {1055, 555, 60, 55};
			SDL_RenderCopy(*renderer,texture.menurolltex,NULL ,&menuroll0Rect); 
			
	}

	if(gamestate->menuroll == 4)
	{
			SDL_Rect menuroll0Rect = {1055, 630, 60, 55};
			SDL_RenderCopy(*renderer,texture.menurolltex,NULL ,&menuroll0Rect); 
			
	}

	
	

	
	SDL_RenderPresent(*renderer);
	SDL_RenderClear(*renderer); 
}