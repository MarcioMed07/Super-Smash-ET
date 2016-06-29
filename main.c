#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "main.h"
#include "logic.h"
#include "states.h"


typedef enum _APPSTATE{
	OPENING,
	MENU,
	OPTIONS,
	HIGHSCORE,
	CREDITOS,
	NEWGAME,
	GAMEOVERWIN,
	GAMEOVERLOSE,
	EXIT,
}APPSTATE;


void init (Gamestate *);

void closing(SDL_Window**,SDL_Renderer**);

int recebeImput(SDL_Event *, Gamestate *,APPSTATE*);

void initwindow(SDL_Window**,SDL_Renderer**);

void salahandler(Gamestate*);


int main(int argc, char const *argv[])
{
	

	APPSTATE state = OPENING;
	srand(time(0));
	

	Gamestate gamestate;
	SDL_Window *window = NULL ; 
	SDL_Renderer *renderer = NULL ;


	int go = 1;
	int pause = 0;


	initwindow(&window,&renderer);

	loadimages(renderer,&texture);

	while(go == 1)
	{
		SDL_Event event;

			
			switch(state)
			{
				case OPENING:
				{

					//opening(&window,&renderer);

					state = MENU;
					break;
				}
				case MENU:
				{
					int decide = 0;
					menu(&window,&renderer);
					while(decide == 0)
					{
						
						decide = recebeImput(&event,&gamestate,&state);
					}
					break;
						
				}
				case OPTIONS:
				{
					int decide = 0;
					while(decide == 0)
					{
						options(&window,&renderer);
						decide = recebeImput(&event,&gamestate,&state);
					}
					break;
				}
				case HIGHSCORE:
				{
					int decide = 0;
					while(decide == 0)
					{
						highscores(&window,&renderer);
						decide = recebeImput(&event,&gamestate,&state);
					}
					break;
				}
				case CREDITOS:
				{
					int decide = 0;
					while(decide == 0)
					{
						credits(&window,&renderer);
						decide = recebeImput(&event,&gamestate,&state);
					}
					break;
				}
				case NEWGAME:
				{
					init(&gamestate);

					int running = 1;

					while(running == 1)
					{
						//printf("life: %d\n",gamestate.player.life);
						unsigned int inicio = 0,fim = 0;

						inicio = SDL_GetTicks();

						int para = recebeImput(&event, &gamestate,&state);

						if(para == 1)
						{
							running = 0;
							
						}

						if (gamestate.pause == 0)
						{				

							logica(&gamestate);	
						}
						
						salahandler(&gamestate);
						desenha(renderer,&gamestate,&texture);
							

						
						if(gamestate.player.life <= 0)
						{						
							state = GAMEOVERLOSE;
							running = 0;
						}

						if(gamestate.victory == 1)
						{
							state = GAMEOVERWIN;
							running = 0;
							puts("yeah");
						}
						else;
							
						//printf("estado: %d\n",gamestate.sala[BOSS].clear );

						fim = SDL_GetTicks();

						if (fim - inicio < 1000/60)
							SDL_Delay(1000/60-(fim-inicio));

						

					}
					break;
				}
				case GAMEOVERWIN:
				{
					int decide = 0;

					while(decide == 0)
					{
						SDL_Texture *win = IMG_LoadTexture(renderer, "images/gameover/win.png");
						SDL_RenderCopy(renderer, win,NULL, 0);
						SDL_RenderPresent(renderer);
						SDL_RenderClear(renderer);   
						
						decide = recebeImput(&event, &gamestate,&state);
					}

					break;
				}
				case GAMEOVERLOSE:
				{
					int decide = 0;

					while(decide == 0)
					{
						SDL_Texture *lose = IMG_LoadTexture(renderer, "images/gameover/lose.png");
						SDL_RenderCopy(renderer, lose,NULL, 0);
						SDL_RenderPresent(renderer);
						SDL_RenderClear(renderer);  
						
						
						decide = recebeImput(&event, &gamestate,&state);
							
					}

					break;
				}
				case EXIT:
				{
					closing(&window,&renderer);
					go = 0;
					break;
				}
			}
		
	}
		

	return 0;
}

void salahandler(Gamestate *gamestate)
{
	int i;
	SDL_Rect playerRect = {	gamestate->player.x,gamestate->player.y,
							gamestate->player.w,gamestate->player.h};

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

	int Px = playerRect.x;
	int PX = playerRect.x + playerRect.w;
	int Py = playerRect.y;
	int PY = playerRect.y + playerRect.h;

	int Pux = portaupRect.x;
	int PuX = portaupRect.x + portaupRect.w;
	int Puy = portaupRect.y;
	int PuY = portaupRect.y + portaupRect.h;

	int Pdx = portadownRect.x;
	int PdX = portadownRect.x + portadownRect.w;
	int Pdy = portadownRect.y;
	int PdY = portadownRect.y + portadownRect.h;

	int Plx = portaleftRect.x;
	int PlX = portaleftRect.x + portaleftRect.w;
	int Ply = portaleftRect.y;
	int PlY = portaleftRect.y + portaleftRect.h;

	int Prx = portarightRect.x;
	int PrX = portarightRect.x + portarightRect.w;
	int Pry = portarightRect.y;
	int PrY = portarightRect.y + portarightRect.h;


	switch(gamestate->salaatual)
	{
		case SALA1:
			gamestate->sala[gamestate->salaatual].x = 0;
		    gamestate->sala[gamestate->salaatual].y = 0;
		    gamestate->sala[gamestate->salaatual].w = 1366;
		    gamestate->sala[gamestate->salaatual].h = 768;
		   // gamestate->sala[gamestate->salaatual].waveatual = 3;
		    if(gamestate->sala[gamestate->salaatual].clear == 1)
		    {
		    	if(!((PX<Prx) || (PrX<Px) || (PY < Pry) || (PrY < Py)))
				{
					gamestate->salaatual = SALA3;
					gamestate->player.x = gamestate->sala[SALA3].portaleft.w - gamestate->sala[SALA4].portaleft.x;
					gamestate->player.y = gamestate->sala[SALA3].portaleft.y + 50 + 1;
					gamestate->rob = 60;
					for(i = 0; i < MAXENEMIES; i++)
				   		enemy[i].on = 0;

				   	for(i = 0; i < MAXENEMIES; i++)
				   		enemymedium[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		lifeplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		speedplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		damageplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma1[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma2[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma3[i].on = 0;
				}
				if(!((PX<Pdx) || (PdX<Px) || (PY < Pdy) || (PdY < Py)))
				{
					gamestate->salaatual = SALA2;
					gamestate->player.x = gamestate->sala[SALA2].portaup.x + 50;
					gamestate->player.y = gamestate->sala[SALA2].portaup.y + 100;
					gamestate->rob = 60;
					for(i = 0; i < MAXENEMIES; i++)
				   		enemy[i].on = 0;

				   	for(i = 0; i < MAXENEMIES; i++)
				   		enemymedium[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		lifeplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		speedplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		damageplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma1[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma2[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma3[i].on = 0;
				}
		    }
			break;//prupru
		case SALA2:
			gamestate->sala[gamestate->salaatual].x = 0;
		    gamestate->sala[gamestate->salaatual].y = 768;
		    gamestate->sala[gamestate->salaatual].w = 1366;
		    gamestate->sala[gamestate->salaatual].h = 768;
		   // gamestate->sala[gamestate->salaatual].waveatual = 3;
		    gamestate->sala[SALA1].portadown.x = 470;
			    gamestate->sala[SALA1].portadown.y = 669;
			    gamestate->sala[SALA1].portadown.w = 356;
			    gamestate->sala[SALA1].portadown.h = 100;
		    if(gamestate->sala[gamestate->salaatual].clear == 1)
		    {
		    	if(!((PX<Prx) || (PrX<Px) || (PY < Pry) || (PrY < Py)))
				{
					gamestate->salaatual = SALA4;
					gamestate->player.x = gamestate->sala[SALA4].portaleft.w - gamestate->sala[SALA4].portaleft.x;
					gamestate->player.y = gamestate->sala[SALA4].portaleft.y ;
					gamestate->rob = 60;
					for(i = 0; i < MAXENEMIES; i++)
				   		enemy[i].on = 0;

				   	for(i = 0; i < MAXENEMIES; i++)
				   		enemymedium[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		lifeplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		speedplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		damageplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma1[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma2[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma3[i].on = 0;
				}
				if(!((PX<Pux) || (PuX<Px) || (PY < Puy) || (PuY < Py)))
				{
					gamestate->salaatual = SALA1;
					gamestate->player.x = gamestate->sala[SALA1].portadown.x + 50;
					gamestate->player.y = gamestate->sala[SALA1].portadown.y - gamestate->player.h - 10;
					gamestate->rob = 60;
					for(i = 0; i < MAXENEMIES; i++)
				   		enemy[i].on = 0;

				   	for(i = 0; i < MAXENEMIES; i++)
				   		enemymedium[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		lifeplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		speedplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		damageplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma1[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma2[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma3[i].on = 0;
				}
		    }
		    break;
		case SALA3:
			gamestate->sala[gamestate->salaatual].x = 1366;
		    gamestate->sala[gamestate->salaatual].y = 0;
		    gamestate->sala[gamestate->salaatual].w = 1366;
		    gamestate->sala[gamestate->salaatual].h = 768;
		    
		   // gamestate->sala[gamestate->salaatual].waveatual = 3;
		    if(gamestate->sala[gamestate->salaatual].clear == 1)
		    {
		    	if(!((PX<Prx) || (PrX<Px) || (PY < Pry) || (PrY < Py)))
				{
					gamestate->salaatual = BOSS;
					gamestate->player.x = gamestate->sala[BONUS].portaleft.x + 100;
					gamestate->player.y = gamestate->sala[BONUS].portaleft.y ;
					gamestate->rob = 60;
					for(i = 0; i < MAXENEMIES; i++)
				   		enemy[i].on = 0;

				   	for(i = 0; i < MAXENEMIES; i++)
				   		enemymedium[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		lifeplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		speedplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		damageplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma1[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma2[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma3[i].on = 0;
				}
				if(!((PX<Pdx) || (PdX<Px) || (PY < Pdy) || (PdY < Py)))
				{
					gamestate->salaatual = SALA4;
					gamestate->player.x = gamestate->sala[SALA4].portaup.x + 50;
					gamestate->player.y = gamestate->sala[SALA4].portaup.y + 100;
					gamestate->rob = 60;
					for(i = 0; i < MAXENEMIES; i++)
				   		enemy[i].on = 0;

				   	for(i = 0; i < MAXENEMIES; i++)
				   		enemymedium[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		lifeplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		speedplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		damageplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma1[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma2[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma3[i].on = 0;
				}
				if(!((PX<Plx) || (PlX<Px) || (PY < Ply) || (PlY < Py)))
				{
					gamestate->salaatual = SALA1;
					gamestate->player.x = gamestate->sala[SALA1].portaright.x - gamestate->player.w - 10;
					gamestate->player.y = gamestate->sala[SALA1].portaright.y + gamestate->sala[SALA1].portaright.h/2;
					gamestate->rob = 60;
					for(i = 0; i < MAXENEMIES; i++)
				   		enemy[i].on = 0;

				   	for(i = 0; i < MAXENEMIES; i++)
				   		enemymedium[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		lifeplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		speedplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		damageplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma1[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma2[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma3[i].on = 0;
				}
		    }
		    break;
		case SALA4:
			gamestate->sala[gamestate->salaatual].x = 1366;
		    gamestate->sala[gamestate->salaatual].y = 768;
		    gamestate->sala[gamestate->salaatual].w = 1366;
		    gamestate->sala[gamestate->salaatual].h = 768;
		    gamestate->sala[SALA3].portaleft.x = 0;
			gamestate->sala[SALA3].portaleft.y = 255;
			gamestate->sala[SALA3].portaleft.w = 100;
			gamestate->sala[SALA3].portaleft.h = 250;
			gamestate->sala[SALA3].portadown.x = 460;
			gamestate->sala[SALA3].portadown.y = 669;
			gamestate->sala[SALA3].portadown.w = 360;
			gamestate->sala[SALA3].portadown.h = 100;
			gamestate->sala[SALA3].portaleft.x = -2;
			gamestate->sala[SALA3].portaleft.y = 255;
			gamestate->sala[SALA3].portaleft.w = 100;
			    gamestate->sala[SALA3].portaleft.h = 252;
		   // gamestate->sala[gamestate->salaatual].waveatual = 3;
		    if(gamestate->sala[gamestate->salaatual].clear == 1)
		    {
		    	if(!((PX<Prx) || (PrX<Px) || (PY < Pry) || (PrY < Py)))
				{
					gamestate->salaatual = BONUS;
					gamestate->player.x = gamestate->sala[BONUS].portaleft.x + 100;
					gamestate->player.y = gamestate->sala[BONUS].portaleft.y ;
					gamestate->rob = 60;
					for(i = 0; i < MAXENEMIES; i++)
				   		enemy[i].on = 0;

				   	for(i = 0; i < MAXENEMIES; i++)
				   		enemymedium[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		lifeplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		speedplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		damageplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma1[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma2[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma3[i].on = 0;
				}
				if(!((PX<Pux) || (PuX<Px) || (PY < Puy) || (PuY < Py)))
				{
					gamestate->salaatual = SALA3;
					gamestate->player.x = gamestate->sala[SALA3].portadown.x + 50;
					gamestate->player.y = gamestate->sala[SALA3].portadown.y  - gamestate->player.h - 10 - 1;
					gamestate->rob = 60;
					for(i = 0; i < MAXENEMIES; i++)
				   		enemy[i].on = 0;

				   	for(i = 0; i < MAXENEMIES; i++)
				   		enemymedium[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		lifeplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		speedplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		damageplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma1[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma2[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma3[i].on = 0;
				}
				if(!((PX<Plx) || (PlX<Px) || (PY < Ply) || (PlY < Py)))
				{
					gamestate->salaatual = SALA2;
					gamestate->player.x = gamestate->sala[SALA2].portaright.x - gamestate->player.w - 10;
					gamestate->player.y = gamestate->sala[SALA2].portaright.y ;
					gamestate->rob = 60;
					for(i = 0; i < MAXENEMIES; i++)
				   		enemy[i].on = 0;

				   	for(i = 0; i < MAXENEMIES; i++)
				   		enemymedium[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		lifeplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		speedplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		damageplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma1[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma2[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma3[i].on = 0;
				}
		    }
		    break;
		case BOSS:
			gamestate->sala[gamestate->salaatual].x = 1366*2;
		    gamestate->sala[gamestate->salaatual].y = 0;
		    gamestate->sala[gamestate->salaatual].w = 1366;
		    gamestate->sala[gamestate->salaatual].h = 768;
		   // gamestate->sala[gamestate->salaatual].waveatual = 3;
		    
		    break;
		case BONUS:
			gamestate->sala[gamestate->salaatual].x = 1366*2;
		    gamestate->sala[gamestate->salaatual].y = 768;
		    gamestate->sala[gamestate->salaatual].w = 1366;
		    gamestate->sala[gamestate->salaatual].h = 768;
		   // gamestate->sala[gamestate->salaatual].waveatual = 3;
		    if(!((PX<Plx) || (PlX<Px) || (PY < Ply) || (PlY < Py)))
			{
				gamestate->salaatual = SALA4;
				gamestate->player.x = gamestate->sala[SALA4].portaright.x - gamestate->player.w - 10;
				gamestate->player.y = gamestate->sala[SALA4].portaright.y ;
				gamestate->rob = 60;
				for(i = 0; i < MAXENEMIES; i++)
				   		enemy[i].on = 0;

				   	for(i = 0; i < MAXENEMIES; i++)
				   		enemymedium[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		lifeplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		speedplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		damageplus[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma1[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma2[i].on = 0;

				   	for(i = 0; i < MAXPOWERUP; i++)
				   		arma3[i].on = 0;
			}
		    break;
	}
}

void init(Gamestate *gamestate)
{

	gamestate->ScreenW = 1366;
	gamestate->ScreenH = 768;	
	gamestate->pause = 0;
	gamestate->victory = 0;


    gamestate->parede.x = 100 ;
    gamestate->parede.y = 100 ;
    gamestate->parede.h = gamestate->ScreenH-200;
    gamestate->parede.w = gamestate->ScreenW-200;

    gamestate->player.w = 86;
    gamestate->player.h = 100;
    gamestate->player.x = gamestate->ScreenW/2 - gamestate->player.w/2 ;
    gamestate->player.y = gamestate->ScreenH/2 - gamestate->player.h/2 ;
    gamestate->player.life = 300;
    gamestate->player.score = 0;
    gamestate->player.speed = 4;
    gamestate->playerup = 0;
    gamestate->playerdown = 0;
    gamestate->playerleft = 0;
    gamestate->playerright = 0;
    gamestate->player.arma = 1;
    gamestate->player.damageplus = 0;

    gamestate->player.down = 0;
	gamestate->player.up = 0;
	gamestate->player.left = 0;
	gamestate->player.right = 0;

	int i;

	for(gamestate->salaatual = SALA1; gamestate->salaatual <= BONUS; gamestate->salaatual++)
		switch(gamestate->salaatual)
		{
			case SALA1:
				gamestate->sala[gamestate->salaatual].x = 0;
			    gamestate->sala[gamestate->salaatual].y = 0;
			    gamestate->sala[gamestate->salaatual].w = 1366;
			    gamestate->sala[gamestate->salaatual].h = 768;
			    gamestate->sala[gamestate->salaatual].waveatual = 2;
			    //gamestate->sala[gamestate->salaatual].enemytype1 = 8;
			    //gamestate->sala[gamestate->salaatual].enemytype2 = 0;
			    //gamestate->sala[gamestate->salaatual].enemytype3 = 0;
			    //gamestate->sala[gamestate->salaatual].enemytypeboss = 0;
			    //gamestate->sala[gamestate->salaatual].waveatual = 3;
			    //gamestate->sala[gamestate->salaatual].clear = 0;
			    for(i = 0; i < 3; i++)
			    {
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasytospawn = 5;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymediumtospawn = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhardtospawn = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemybosstospawn = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasy = 5;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymedium = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhard = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyboss = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasyleft = 5;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymediumleft = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhardleft = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemybossleft = 0;
			    	gamestate->sala[gamestate->salaatual].clear = 0;
			    }
			    gamestate->sala[gamestate->salaatual].portaup.x = 0;
			    gamestate->sala[gamestate->salaatual].portaup.y = 0;
			    gamestate->sala[gamestate->salaatual].portaup.w = 0;
			    gamestate->sala[gamestate->salaatual].portaup.h = 0;
			    gamestate->sala[gamestate->salaatual].portadown.x = 470;
			    gamestate->sala[gamestate->salaatual].portadown.y = 669;
			    gamestate->sala[gamestate->salaatual].portadown.w = 356;
			    gamestate->sala[gamestate->salaatual].portadown.h = 100;
			    gamestate->sala[gamestate->salaatual].portaleft.x = 0;
			    gamestate->sala[gamestate->salaatual].portaleft.y = 0;
			    gamestate->sala[gamestate->salaatual].portaleft.w = 0;
			    gamestate->sala[gamestate->salaatual].portaleft.h = 0;
			    gamestate->sala[gamestate->salaatual].portaright.x = 1266;
			    gamestate->sala[gamestate->salaatual].portaright.y = 255;
			    gamestate->sala[gamestate->salaatual].portaright.w = 100;
			    gamestate->sala[gamestate->salaatual].portaright.h = 250;
			    break;
			case SALA2:
				gamestate->sala[gamestate->salaatual].x = 0;
			    gamestate->sala[gamestate->salaatual].y = 768;
			    gamestate->sala[gamestate->salaatual].w = 1366;
			    gamestate->sala[gamestate->salaatual].h = 768;
			    gamestate->sala[gamestate->salaatual].waveatual = 2;
			    //gamestate->sala[gamestate->salaatual].enemytype1 = 6;
			    //gamestate->sala[gamestate->salaatual].enemytype2 = 3;
			    //gamestate->sala[gamestate->salaatual].enemytype3 = 1;
			    //gamestate->sala[gamestate->salaatual].enemytypeboss = 0;
			    //gamestate->sala[gamestate->salaatual].wave = 2;
			    //gamestate->sala[gamestate->salaatual].clear = 1;
			    for(i = 0; i < 3; i++)
			    {
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasytospawn = 4;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymediumtospawn = 2;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhardtospawn = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemybosstospawn = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasy = 4;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymedium = 2;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhard = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyboss = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasyleft = 4;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymediumleft = 2;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhardleft = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemybossleft = 0;
			    	gamestate->sala[gamestate->salaatual].clear = 0;
			    }
			    gamestate->sala[gamestate->salaatual].portaup.x = 470;
			    gamestate->sala[gamestate->salaatual].portaup.y = 0;
			    gamestate->sala[gamestate->salaatual].portaup.w = 356;
			    gamestate->sala[gamestate->salaatual].portaup.h = 100;
			    gamestate->sala[gamestate->salaatual].portadown.x = 0;
			    gamestate->sala[gamestate->salaatual].portadown.y = 0;
			    gamestate->sala[gamestate->salaatual].portadown.w = 0;
			    gamestate->sala[gamestate->salaatual].portadown.h = 0;
			    gamestate->sala[gamestate->salaatual].portaleft.x = 0;
			    gamestate->sala[gamestate->salaatual].portaleft.y = 0;
			    gamestate->sala[gamestate->salaatual].portaleft.w = 0;
			    gamestate->sala[gamestate->salaatual].portaleft.h = 0;
			    gamestate->sala[gamestate->salaatual].portaright.x = 1266;
			    gamestate->sala[gamestate->salaatual].portaright.y = 255;
			    gamestate->sala[gamestate->salaatual].portaright.w = 100;
			    gamestate->sala[gamestate->salaatual].portaright.h = 250;
			    break;
			case SALA3:
				gamestate->sala[gamestate->salaatual].x = 1366;
			    gamestate->sala[gamestate->salaatual].y = 0;
			    gamestate->sala[gamestate->salaatual].w = 1366;
			    gamestate->sala[gamestate->salaatual].h = 768;
			    gamestate->sala[gamestate->salaatual].waveatual = 2;
			    //gamestate->sala[gamestate->salaatual].enemytype1 = 7;
			    //gamestate->sala[gamestate->salaatual].enemytype2 = 3;
			    //gamestate->sala[gamestate->salaatual].enemytype3 = 2;
			   // gamestate->sala[gamestate->salaatual].enemytypeboss = 0;
			    //gamestate->sala[gamestate->salaatual].wave = 3;
			    //gamestate->sala[gamestate->salaatual].clear = 1;
			    for(i = 0; i < 3; i++)
			    {
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasytospawn = 7;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymediumtospawn = 3;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhardtospawn = 1;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemybosstospawn = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasy = 7;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymedium = 3;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhard = 1;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyboss = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasyleft = 7;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymediumleft = 3;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhardleft = 1;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemybossleft = 0;
			    	gamestate->sala[gamestate->salaatual].clear = 0;
			    }
			    gamestate->sala[gamestate->salaatual].portaup.x = 0;
			    gamestate->sala[gamestate->salaatual].portaup.y = 0;
			    gamestate->sala[gamestate->salaatual].portaup.w = 0;
			    gamestate->sala[gamestate->salaatual].portaup.h = 0;
			    gamestate->sala[gamestate->salaatual].portadown.x = 460;
			    gamestate->sala[gamestate->salaatual].portadown.y = 669;
			    gamestate->sala[gamestate->salaatual].portadown.w = 360;
			    gamestate->sala[gamestate->salaatual].portadown.h = 100;
			    gamestate->sala[gamestate->salaatual].portaleft.x = -2;
			    gamestate->sala[gamestate->salaatual].portaleft.y = 255;
			    gamestate->sala[gamestate->salaatual].portaleft.w = 100;
			    gamestate->sala[gamestate->salaatual].portaleft.h = 252;
			    gamestate->sala[gamestate->salaatual].portaright.x = 1266;
			    gamestate->sala[gamestate->salaatual].portaright.y = 250;
			    gamestate->sala[gamestate->salaatual].portaright.w = 100;
			    gamestate->sala[gamestate->salaatual].portaright.h = 260;
			    break;
			case SALA4:
				gamestate->sala[gamestate->salaatual].x = 1366;
			    gamestate->sala[gamestate->salaatual].y = 768;
			    gamestate->sala[gamestate->salaatual].w = 1366;
			    gamestate->sala[gamestate->salaatual].h = 768;
			    gamestate->sala[gamestate->salaatual].waveatual = 2;
			   // gamestate->sala[gamestate->salaatual].enemytype1 = 7;
			   // gamestate->sala[gamestate->salaatual].enemytype2 = 4;
			   // gamestate->sala[gamestate->salaatual].enemytype3 = 3;
			   // gamestate->sala[gamestate->salaatual].enemytypeboss = 0;
			   // gamestate->sala[gamestate->salaatual].wave = 3;
			   // gamestate->sala[gamestate->salaatual].clear = 1;
			    for(i = 0; i < 3; i++)
			    {
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasytospawn = 4;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymediumtospawn = 5;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhardtospawn = 10;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemybosstospawn = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasy = 4;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymedium = 5;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhard = 10;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyboss = 0;
			    	gamestate->sala[gamestate->salaatual].clear = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasyleft = 4;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymediumleft = 5;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhardleft = 10;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemybossleft = 0;
			    }
			    gamestate->sala[gamestate->salaatual].portaup.x = 1366/2 - 370/2;
			    gamestate->sala[gamestate->salaatual].portaup.y = 0;
			    gamestate->sala[gamestate->salaatual].portaup.w = 370;
			    gamestate->sala[gamestate->salaatual].portaup.h = 100;
			    gamestate->sala[gamestate->salaatual].portadown.x = 0;
			    gamestate->sala[gamestate->salaatual].portadown.y = 0;
			    gamestate->sala[gamestate->salaatual].portadown.w = 0;
			    gamestate->sala[gamestate->salaatual].portadown.h = 0;
			    gamestate->sala[gamestate->salaatual].portaleft.x = 0;
			    gamestate->sala[gamestate->salaatual].portaleft.y = 261;
			    gamestate->sala[gamestate->salaatual].portaleft.w = 100;
			    gamestate->sala[gamestate->salaatual].portaleft.h = 240;
			    gamestate->sala[gamestate->salaatual].portaright.x = 1266;
			    gamestate->sala[gamestate->salaatual].portaright.y = 255;
			    gamestate->sala[gamestate->salaatual].portaright.w = 100;
			    gamestate->sala[gamestate->salaatual].portaright.h = 250;
			    break;
			case BOSS:
				gamestate->sala[gamestate->salaatual].x = 1366*2;
			    gamestate->sala[gamestate->salaatual].y = 0;
			    gamestate->sala[gamestate->salaatual].w = 1366;
			    gamestate->sala[gamestate->salaatual].h = 768;
			    gamestate->sala[gamestate->salaatual].waveatual = 0;
			    //gamestate->sala[gamestate->salaatual].enemytype1 = 0;
			    //gamestate->sala[gamestate->salaatual].enemytype2 = 0;
			    //gamestate->sala[gamestate->salaatual].enemytype3 = 0;
			    //gamestate->sala[gamestate->salaatual].enemytypeboss = 1;
			    //gamestate->sala[gamestate->salaatual].wave = 1;
			    gamestate->sala[gamestate->salaatual].clear = 0;
			    for(i = 0; i < 3; i++)
			    {
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasytospawn = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymediumtospawn = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhardtospawn = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemybosstospawn = 1;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasy = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymedium = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhard = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyboss = 1;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasyleft = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymediumleft = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhardleft = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemybossleft = 1;
			    	gamestate->sala[gamestate->salaatual].clear = 0;
			    }
			    gamestate->sala[gamestate->salaatual].portaup.x = 0;
			    gamestate->sala[gamestate->salaatual].portaup.y = 0;
			    gamestate->sala[gamestate->salaatual].portaup.w = 0;
			    gamestate->sala[gamestate->salaatual].portaup.h = 0;
			    gamestate->sala[gamestate->salaatual].portadown.x = 0;
			    gamestate->sala[gamestate->salaatual].portadown.y = 0;
			    gamestate->sala[gamestate->salaatual].portadown.w = 0;
			    gamestate->sala[gamestate->salaatual].portadown.h = 0;
				gamestate->sala[gamestate->salaatual].portaleft.x = 0;
			    gamestate->sala[gamestate->salaatual].portaleft.y = 261;
			    gamestate->sala[gamestate->salaatual].portaleft.w = 100;
			    gamestate->sala[gamestate->salaatual].portaleft.h = 240;
			    gamestate->sala[gamestate->salaatual].portaright.x = 0;
			    gamestate->sala[gamestate->salaatual].portaright.y = 0;
			    gamestate->sala[gamestate->salaatual].portaright.w = 0;
			    gamestate->sala[gamestate->salaatual].portaright.h = 0;
			    break;
			case BONUS:
				gamestate->sala[gamestate->salaatual].x = 1366*2;
			    gamestate->sala[gamestate->salaatual].y = 768;
			    gamestate->sala[gamestate->salaatual].w = 1366;
			    gamestate->sala[gamestate->salaatual].h = 768;
			    gamestate->sala[gamestate->salaatual].waveatual = 2;
			    //gamestate->sala[gamestate->salaatual].enemytype1 = 0;
			    //gamestate->sala[gamestate->salaatual].enemytype2 = 0;
			    //gamestate->sala[gamestate->salaatual].enemytype3 = 0;
			    //gamestate->sala[gamestate->salaatual].enemytypeboss = 0;
			    //gamestate->sala[gamestate->salaatual].wave = 0;
			    //gamestate->sala[gamestate->salaatual].clear = 1;
			    for(i = 0; i < 3; i++)
			    {
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasytospawn = 20;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymediumtospawn = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhardtospawn = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemybosstospawn = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasy = 20;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymedium = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhard = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyboss = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasyleft = 20;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymediumleft = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhardleft = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemybossleft = 0;
			    	gamestate->sala[gamestate->salaatual].clear = 0;
			    }
			    gamestate->sala[gamestate->salaatual].portaup.x = 0;
			    gamestate->sala[gamestate->salaatual].portaup.y = 0;
			    gamestate->sala[gamestate->salaatual].portaup.w = 0;
			    gamestate->sala[gamestate->salaatual].portaup.h = 0;
			    gamestate->sala[gamestate->salaatual].portadown.x = 0;
			    gamestate->sala[gamestate->salaatual].portadown.y = 0;
			    gamestate->sala[gamestate->salaatual].portadown.w = 0;
			    gamestate->sala[gamestate->salaatual].portadown.h = 0;
			    gamestate->sala[gamestate->salaatual].portaleft.x = 0;
			    gamestate->sala[gamestate->salaatual].portaleft.y = 261;
			    gamestate->sala[gamestate->salaatual].portaleft.w = 100;
			    gamestate->sala[gamestate->salaatual].portaleft.h = 240;
			    gamestate->sala[gamestate->salaatual].portaright.x = 0;
			    gamestate->sala[gamestate->salaatual].portaright.y = 0;
			    gamestate->sala[gamestate->salaatual].portaright.w = 0;
			    gamestate->sala[gamestate->salaatual].portaright.h = 0;
			    break;
		}


	gamestate->salaatual = SALA1;

	    
    gamestate->player.angulo = 0;

    gamestate->rof = 0;
	gamestate->rob = 60;


    gamestate->mousex = 600;
    gamestate->mousey = 600;

    
    for(i = 0; i < MAXENEMIES; i++)
   		enemy[i].on = 0;

   	for(i = 0; i < MAXENEMIES; i++)
   		enemymedium[i].on = 0;

   	for(i = 0; i < MAXENEMIES; i++)
   		enemyboss[i].on = 0;

   	for(i = 0; i < MAXPOWERUP; i++)
   		lifeplus[i].on = 0;

   	for(i = 0; i < MAXPOWERUP; i++)
   		speedplus[i].on = 0;

   	for(i = 0; i < MAXPOWERUP; i++)
   		damageplus[i].on = 0;

   	for(i = 0; i < MAXPOWERUP; i++)
   		arma1[i].on = 0;

   	for(i = 0; i < MAXPOWERUP; i++)
   		arma2[i].on = 0;

   	for(i = 0; i < MAXPOWERUP; i++)
   		arma3[i].on = 0;


				
    int j;
    for(j = 0; j < MAXBULLETS; j++)
    {
    	bullet[j].on = 0;
			bullet[j].x = 0;
			bullet[j].y = 0;
			bullet[j].xinit = 0;
			bullet[j].yinit = 0;
			bullet[j].direction = NONE;
			bullet[j].speed = 0;
    }

    SDL_ShowCursor(SDL_DISABLE);

}

void closing(SDL_Window **window,SDL_Renderer **renderer)
{
	SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow(*window);

    SDL_Quit();
}



int recebeImput(SDL_Event *event, Gamestate *gamestate,APPSTATE* state)
{
	while (SDL_PollEvent(event)) 
	{

			switch(*state)
			{
				case OPENING:
				{
					if(event->type == SDL_KEYDOWN)
					{
						if(SDLK_RETURN == event->key.keysym.sym) 
						{
				            *state = MENU;
				            return 1;
						}
					}
					break;
				}
				case MENU:
				{

					if(event->type == SDL_QUIT)
					{
						*state = EXIT;
						return 1;
					}
					if(event->type == SDL_KEYDOWN)
					{
						if(SDLK_1 == event->key.keysym.sym) 
						{
				            *state = NEWGAME;
				            return 1;
						}
				        if(SDLK_2 == event->key.keysym.sym) 
				        {
				            *state = OPTIONS;
				            return 1;
				        }
				        if(SDLK_3 == event->key.keysym.sym) 
				        {
				            *state = CREDITOS;
				            return 1;
				        }
				        if(SDLK_4 == event->key.keysym.sym) 
				        {
				            *state = HIGHSCORE;
				            return 1;
				        }
				        if(SDLK_5 == event->key.keysym.sym || SDLK_ESCAPE == event->key.keysym.sym) 
				        {
				        	*state = EXIT;
				        	return 1;
				        }
				    }
					break;					
				}
				case OPTIONS:
				{
					if(event->type == SDL_QUIT)
					{
						*state = EXIT;
						return 1;
					}
					if(event->type == SDL_KEYDOWN)
					{
						
				        if(SDLK_2 == event->key.keysym.sym) 
				        {
				            *state = MENU;
				            return 1;
				        }
				    }
					break;
				}
				case HIGHSCORE:
				{
					if(event->type == SDL_QUIT)
					{
						*state = EXIT;
						return 1;
					}
					if(event->type == SDL_KEYDOWN)
					{
						
				        if(SDLK_2 == event->key.keysym.sym) 
				        {
				            *state = MENU;
				            return 1;
				        }
				    }
					break;
				}
				case CREDITOS:
				{
					if(event->type == SDL_QUIT)
					{
						*state = EXIT;
						return 1;
					}
					if(event->type == SDL_KEYDOWN)
					{
						
				        if(SDLK_2 == event->key.keysym.sym) 
				        {
				            *state = MENU;
				            return 1;
				        }
				    }
					break;
				}
				case NEWGAME:
				{	

					if(event->type == SDL_QUIT)
					{
						*state = EXIT;
						return 1;
					}
					if(event->type == SDL_KEYDOWN)
					{
						if(SDLK_s == event->key.keysym.sym) 
				           gamestate->playerdown = 1; 
				        else if(SDLK_w == event->key.keysym.sym) 
				            gamestate->playerup = 1;
				        if(SDLK_a == event->key.keysym.sym) 
				            gamestate->playerleft = 1;
				        else if(SDLK_d == event->key.keysym.sym) 
				            gamestate->playerright = 1;
				        

				        if(SDLK_DOWN == event->key.keysym.sym) 
				           gamestate->player.down = 1; 
				        if(SDLK_UP == event->key.keysym.sym) 
				            gamestate->player.up = 1;
				        if(SDLK_LEFT == event->key.keysym.sym) 
				            gamestate->player.left = 1;
				        if(SDLK_RIGHT == event->key.keysym.sym) 
				            gamestate->player.right = 1;



				        if(SDLK_ESCAPE == event->key.keysym.sym)
						{
							*state = MENU;
							return 1;
						}

						
				    }
				        	

				    if(event->type == SDL_KEYUP)
					{
				        if(SDLK_s == event->key.keysym.sym) 
				            gamestate->playerdown = 0;
				        else if(SDLK_w == event->key.keysym.sym) 
				            gamestate->playerup = 0;
				        if(SDLK_a == event->key.keysym.sym) 
				           	gamestate->playerleft = 0;
				        else if(SDLK_d == event->key.keysym.sym) 
				            gamestate->playerright = 0;

				        if(SDLK_DOWN == event->key.keysym.sym) 
				           gamestate->player.down = 0; 
				        if(SDLK_UP == event->key.keysym.sym) 
				            gamestate->player.up = 0;
				        if(SDLK_LEFT == event->key.keysym.sym) 
				            gamestate->player.left = 0;
				        if(SDLK_RIGHT == event->key.keysym.sym) 
				            gamestate->player.right = 0;

				        if(gamestate->pause == 0)
						{
							if(SDLK_p == event->key.keysym.sym)
							{
								gamestate->pause = 1;
								//puts("pra pausar");
							}	
						}
						else if(gamestate->pause == 1)
						{
							if(SDLK_p == event->key.keysym.sym)
							{
								gamestate->pause = 0;
								//puts("pra retornar");
							}
							if(SDLK_r == event->key.keysym.sym)
							{
								*state = NEWGAME;
								return 1;
							}	
						}
				    }
					
					break;
				}
				case GAMEOVERWIN:
				{
					switch (event->type) 
					{
						case SDL_QUIT:					
							*state = EXIT;				
							break;
						case SDL_KEYDOWN:
							if(SDLK_ESCAPE == event->key.keysym.sym)
							{
								*state = MENU;
								return 1;
																		
							}
							if(SDLK_r == event->key.keysym.sym)
							{
								*state = NEWGAME;
								return 1;
							}
							break;
					}
				}
					break;

				case GAMEOVERLOSE:
				{
					
					switch (event->type) 
					{
						case SDL_QUIT:					
							*state = EXIT;				
							break;
						case SDL_KEYDOWN:
							if(SDLK_ESCAPE == event->key.keysym.sym)
							{
								*state = MENU;
								return 1;
																		
							}
							if(SDLK_r == event->key.keysym.sym)
							{
								*state = NEWGAME;
								return 1;
							}
							break;
					}
				
					break;
				}
				case EXIT:
				{
					break;
				}
			}
	}

	return 0;
        	
}

void initwindow(SDL_Window **window,SDL_Renderer **renderer)
{
	int ScreenW = 1366;
	int ScreenH = 768;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Erro ao iniciar SDL! Erro: %s\n",SDL_GetError() );
        SDL_Quit();
        exit(1);
    }
    else
    {
        *window = SDL_CreateWindow( "Jogo",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    ScreenW,
                                   	ScreenH,
                                   	SDL_WINDOW_SHOWN|
									SDL_WINDOW_RESIZABLE|
									SDL_WINDOW_FULLSCREEN_DESKTOP);
        if (*window == NULL)
        {
            printf("Erro ao criar a janela! Erro: %s\n",SDL_GetError());
            SDL_Quit();
            exit(1);
        }
        else
        {
            *renderer = SDL_CreateRenderer(	*window,
            								-1,
            								SDL_RENDERER_ACCELERATED);
        	SDL_RenderSetLogicalSize(*renderer, ScreenW, ScreenH);
        }
    }
}
