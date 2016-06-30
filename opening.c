#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "main.h"

void opening(SDL_Window** window, SDL_Renderer**renderer,SDL_Event * event, Gamestate *gamestate,APPSTATE*state)
{
	

    int opacidade = 0;

    int go = 0;

	

	

	while(opacidade < 255 && go == 0)
	{
		
		

		
		SDL_SetTextureBlendMode(texture.openingtex,SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(texture.openingtex,opacidade);
		SDL_RenderCopy(*renderer, texture.openingtex,NULL, 0);
		SDL_SetRenderDrawColor(*renderer, 255, 255,255, 255);

		go = recebeImput(event,gamestate,state);	


		opacidade += 1;	
		SDL_Delay(8);

		SDL_RenderPresent(*renderer);
		SDL_RenderClear(*renderer);  
	}

	if(go == 0)
	{	
		SDL_Delay(1000);
		opacidade = 255;
	}

	while(opacidade > 0 && go ==0)
	{
		
		

		
		SDL_SetTextureBlendMode(texture.openingtex,SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(texture.openingtex,opacidade);
		SDL_RenderCopy(*renderer, texture.openingtex,NULL, 0);
		//SDL_SetRenderDrawColor(*renderer, 255, 255,255, 255);
		

		go = recebeImput(event,gamestate,state);

		opacidade -= 1;
		SDL_Delay(8);

		SDL_RenderPresent(*renderer);
		SDL_RenderClear(*renderer);  
	}

	while(opacidade < 255 && go ==0)
	{
		
		

		
		SDL_SetTextureBlendMode(texture.logotex,SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(texture.logotex,opacidade);
		SDL_RenderCopy(*renderer, texture.logotex,NULL, 0);
		//SDL_SetRenderDrawColor(*renderer, 255, 255,255, 255);
		go = recebeImput(event,gamestate,state);
	


		opacidade += 1;	
		SDL_Delay(8);

		SDL_RenderPresent(*renderer);
		SDL_RenderClear(*renderer);  
	}
	if(go == 0)
	{	
		SDL_Delay(1000);
		opacidade = 255;
	}

	while(opacidade > 0 && go ==0)
	{
		
		

		
		SDL_SetTextureBlendMode(texture.logotex,SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(texture.logotex,opacidade);
		SDL_RenderCopy(*renderer, texture.logotex,NULL, 0);
		SDL_SetRenderDrawColor(*renderer, 0, 0,0, 0);
		go = recebeImput(event,gamestate,state);


		opacidade -= 1;
		SDL_Delay(8);

		SDL_RenderPresent(*renderer);
		SDL_RenderClear(*renderer);  
	}

}