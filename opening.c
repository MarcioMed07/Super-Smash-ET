#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>

void opening(SDL_Window** window, SDL_Renderer**renderer)
{
	

    int opacidade = 0;

	

	

	while(opacidade < 255)
	{
		
		

		SDL_Texture *openingtex = IMG_LoadTexture(*renderer, "images/opening/sdlop.png");
		SDL_SetTextureBlendMode(openingtex,SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(openingtex,opacidade);
		SDL_RenderCopy(*renderer, openingtex,NULL, 0);
		SDL_SetRenderDrawColor(*renderer, 255, 255,255, 255);

	


		opacidade += 2;	
		SDL_RenderPresent(*renderer);
		SDL_RenderClear(*renderer);  
	}

	SDL_Delay(1000);
	opacidade = 255;

	while(opacidade > 0)
	{
		
		

		SDL_Texture *openingtex = IMG_LoadTexture(*renderer, "images/opening/sdlop.png");
		SDL_SetTextureBlendMode(openingtex,SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(openingtex,opacidade);
		SDL_RenderCopy(*renderer, openingtex,NULL, 0);
		SDL_SetRenderDrawColor(*renderer, 255, 255,255, 255);
		


		opacidade -= 2;
		SDL_RenderPresent(*renderer);
		SDL_RenderClear(*renderer);  
	}

}