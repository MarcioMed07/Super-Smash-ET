#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "main.h"



void menu(SDL_Window** window, SDL_Renderer**renderer)
{
	int opacidade = 0;
	SDL_SetRenderDrawColor(*renderer, 0, 0,0, 0);
	


	while(opacidade < 255)
	{

		
	
		SDL_Texture *menutex = IMG_LoadTexture(*renderer, "images/menu/menu.png");
		SDL_SetTextureBlendMode(menutex,SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(menutex,opacidade);
		SDL_RenderCopy(*renderer, menutex,NULL, 0);
		SDL_SetRenderDrawColor(*renderer, 0, 0,0, 0);


		opacidade += 45;	
		SDL_RenderPresent(*renderer);
		SDL_RenderClear(*renderer);  
	}

																																																																																																																																																																																																																																																																																																																																								

}

void desenhamenu(SDL_Renderer** renderer, Gamestate *gamestate)
{
	
	SDL_Texture *menutex = IMG_LoadTexture(*renderer, "images/menu/menu.png");
	SDL_RenderCopy(*renderer, menutex,NULL, 0);
	
	
	SDL_Texture *menurolltex = IMG_LoadTexture(*renderer, "images/menu/roll.png");

	/*switch(gamestate->menuroll)
	{
		case 0:
			
			
			
			break;
		 case 1:
		 	
		 	//SDL_Rect menuroll1Rect = {1055, 460, 60, 55};
		 	SDL_RenderCopy(*renderer,menurolltex,NULL ,NULL);//&menuroll1Rect); 
		 	puts("1");


			
			break;
		/*case 2:
			menurollRect.x = ;
			menurollRect.y = ;
			menurollRect.w = ;
			menurollRect.h = ;
			break;
		case 3:
			menurollRect.x = ;
			menurollRect.y = ;
			menurollRect.w = ;
			menurollRect.h = ;
			break;
		case 4: 
			menurollRect.x = ;
			menurollRect.y = ;
			menurollRect.w = ;
			menurollRect.h = ;
			break;
	}*/

	if(gamestate->menuroll == 0)
	{
			SDL_Rect menuroll0Rect = {1055, 330, 60, 55};
			SDL_RenderCopy(*renderer,menurolltex,NULL ,&menuroll0Rect); 
			
	}

	if(gamestate->menuroll == 1)
	{
			SDL_Rect menuroll0Rect = {1055, 405, 60, 55};
			SDL_RenderCopy(*renderer,menurolltex,NULL ,&menuroll0Rect); 
			
	}

	if(gamestate->menuroll == 2)
	{
			SDL_Rect menuroll0Rect = {1055, 480, 60, 55};
			SDL_RenderCopy(*renderer,menurolltex,NULL ,&menuroll0Rect); 
			
	}

	if(gamestate->menuroll == 3)
	{
			SDL_Rect menuroll0Rect = {1055, 555, 60, 55};
			SDL_RenderCopy(*renderer,menurolltex,NULL ,&menuroll0Rect); 
			
	}

	if(gamestate->menuroll == 4)
	{
			SDL_Rect menuroll0Rect = {1055, 630, 60, 55};
			SDL_RenderCopy(*renderer,menurolltex,NULL ,&menuroll0Rect); 
			
	}

	
	

	
	SDL_RenderPresent(*renderer);
	SDL_RenderClear(*renderer); 
}