#include <SDL2/SDL.h>
#include "main.h"
#include "logic.h"
#include <SDL2/SDL_image.h>


void loadimages(SDL_Renderer* renderer,Texture *texture)
{
	texture->backgroundtex = IMG_LoadTexture(renderer, "images/game/backgroundfull.png");
	texture->playertex = IMG_LoadTexture(renderer, "images/game/player.png");
	texture->mousetex = IMG_LoadTexture(renderer, "images/game/mouse.png");
	texture->bullettex = IMG_LoadTexture(renderer, "images/game/bullet.png");
	texture->enemytex = IMG_LoadTexture(renderer, "images/game/enemy.png");

	if (texture->backgroundtex == NULL)
	{
		fprintf(stderr, "fodeu\n%s", SDL_GetError());
	}
}

void desenha(SDL_Renderer* renderer, Gamestate *gamestate,Texture *texture)
{	
	
	SDL_Rect salaRect = {gamestate->sala[gamestate->salaatual].x, gamestate->sala[gamestate->salaatual].y, gamestate->sala[gamestate->salaatual].w, gamestate->sala[gamestate->salaatual].h};
	SDL_RenderCopy(renderer, texture->backgroundtex,&salaRect ,NULL);                        
                                 

    

	
	//SDL_Rect mouseRect = {gamestate->mousex,gamestate->mousey,20,20};
	//SDL_RenderCopy(renderer, texture->mousetex, NULL, &mouseRect);




	int j;
	for(j = 0; j< MAXBULLETS; j++)
	{
		if(bullet[j].on == 1)
		{
			SDL_Rect bulletRect = {bullet[j].x,bullet[j].y,5,5};
			SDL_RenderCopy(renderer, texture->bullettex, NULL, &bulletRect);
		}
	}
	
	int i;
	for(i = 0; i< MAXENEMIES; i++)
	{
		if(enemy[i].on == 1)
		{
			SDL_Rect enemyRect = {enemy[i].x,enemy[i].y,enemy[i].w,enemy[i].h};
			SDL_RenderCopy(renderer, texture->enemytex, NULL, &enemyRect);
		}
	}

	SDL_Rect playerRect = {	gamestate->player.x,gamestate->player.y,
							gamestate->player.w,gamestate->player.h};

	

	if( gamestate->player.down == 1 && gamestate->player.left == 0 && gamestate->player.right == 0)
	{
		gamestate->player.angulo = 180;
	}
	 if ( gamestate->player.up == 1 && gamestate->player.left == 0 && gamestate->player.right == 0)
	{
		gamestate->player.angulo = 360;
	}
	if (gamestate->player.left == 1 && gamestate->player.up == 0 && gamestate->player.down == 0)
	{
		gamestate->player.angulo = 270;
	}
	if (gamestate->player.right == 1 && gamestate->player.up == 0 && gamestate->player.down == 0)
	{
		gamestate->player.angulo = 90;
	}
	if (gamestate->player.right == 1 && gamestate->player.up == 1)
	{
		gamestate->player.angulo = 45;
	}
	if (gamestate->player.right == 1 && gamestate->player.down == 1)
	{
		gamestate->player.angulo = 135;
	}
	if (gamestate->player.left == 1 && gamestate->player.up == 1)
	{
		gamestate->player.angulo = 315;
	}
	if (gamestate->player.left == 1 && gamestate->player.down == 1)
	{
		gamestate->player.angulo = 225;
	}

	SDL_RenderCopyEx(renderer, texture->playertex,NULL, &playerRect,gamestate->player.angulo,NULL,SDL_FLIP_HORIZONTAL);

	
	SDL_Rect portadownRect = {	gamestate->sala[gamestate->salaatual].portadown.x,
								gamestate->sala[gamestate->salaatual].portadown.y,
								gamestate->sala[gamestate->salaatual].portadown.w,
								gamestate->sala[gamestate->salaatual].portadown.h};

	SDL_Rect portaupRect = {	gamestate->sala[gamestate->salaatual].portaup.x,
								gamestate->sala[gamestate->salaatual].portaup.y,
								gamestate->sala[gamestate->salaatual].portaup.w,
								gamestate->sala[gamestate->salaatual].portaup.h};

	SDL_Rect portaleftRect = {	gamestate->sala[gamestate->salaatual].portaleft.x,
								gamestate->sala[gamestate->salaatual].portaleft.y,
								gamestate->sala[gamestate->salaatual].portaleft.w,
								gamestate->sala[gamestate->salaatual].portaleft.h};

	SDL_Rect portarightRect = {	gamestate->sala[gamestate->salaatual].portaright.x,
								gamestate->sala[gamestate->salaatual].portaright.y,
								gamestate->sala[gamestate->salaatual].portaright.w,
								gamestate->sala[gamestate->salaatual].portaright.h};

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &portarightRect);
	SDL_RenderFillRect(renderer, &portaupRect);
	SDL_RenderFillRect(renderer, &portaleftRect);
	SDL_RenderFillRect(renderer, &portadownRect);
	



	

	SDL_Rect playerlifeRect = {100,50,gamestate->player.life , 10};
	SDL_SetRenderDrawColor(renderer, 100, 255, 100, 255);
	SDL_RenderFillRect(renderer, &playerlifeRect);


	SDL_SetRenderDrawColor(renderer, 120, 69,19, 255);

	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);    

}