#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>



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