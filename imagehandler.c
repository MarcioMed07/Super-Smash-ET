#include <SDL2/SDL.h>
#include "main.h"
#include "logic.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>


void loadimages(SDL_Renderer* renderer,Texture *texture)
{
	texture->backgroundtex = IMG_LoadTexture(renderer, "images/game/backgroundfull.png");
	texture->pretotex = IMG_LoadTexture(renderer, "images/gameover/preto.png");
	texture->brancotex = IMG_LoadTexture(renderer, "images/gameover/branco.png");
	
	texture->mousetex = IMG_LoadTexture(renderer, "images/game/mouse.png");
	texture->bullettex = IMG_LoadTexture(renderer, "images/game/bullet.png");

	texture->enemytex = IMG_LoadTexture(renderer, "images/game/enemy.png");
	texture->enemymediumtex = IMG_LoadTexture(renderer, "images/game/medium.png");
	texture->enemybosstex = IMG_LoadTexture(renderer, "images/game/boss.png");

	texture->portauptex = IMG_LoadTexture(renderer, "images/game/up.png");
	texture->portadowntex = IMG_LoadTexture(renderer, "images/game/down.png");
	texture->portalefttex = IMG_LoadTexture(renderer, "images/game/left.png");
	texture->portarighttex = IMG_LoadTexture(renderer, "images/game/right.png");

	texture->pausetex = IMG_LoadTexture(renderer, "images/game/pause.png");

	texture->lifeplustex = IMG_LoadTexture(renderer, "images/powerups/life.png");
	texture->speedplustex = IMG_LoadTexture(renderer, "images/powerups/speed.png");
	texture->damageplustex = IMG_LoadTexture(renderer, "images/powerups/damage.png");
	texture->arma1tex = IMG_LoadTexture(renderer, "images/powerups/1.png");
	texture->arma2tex = IMG_LoadTexture(renderer, "images/powerups/2.png");
	texture->arma3tex = IMG_LoadTexture(renderer, "images/powerups/3.png");

	texture->lifebar = IMG_LoadTexture(renderer, "images/game/lifebar.png");
	texture->howtopausetex = IMG_LoadTexture(renderer, "images/game/howtopause.png");

	texture->playerw1tex = IMG_LoadTexture(renderer, "images/game/playerw1.png");
	texture->playerw2tex = IMG_LoadTexture(renderer, "images/game/playerw2.png");
	texture->playerw3tex = IMG_LoadTexture(renderer, "images/game/playerw3.png");


	texture->gameintrotex = IMG_LoadTexture(renderer, "images/game/historia.png");
	texture->instructionstex = IMG_LoadTexture(renderer, "images/game/instructions.png");

	texture->wintex = IMG_LoadTexture(renderer, "images/gameover/win.png");
	texture->losetex = IMG_LoadTexture(renderer, "images/gameover/lose.png");

	texture->openingtex = IMG_LoadTexture(renderer, "images/opening/sdlop.png");
	texture->logotex = IMG_LoadTexture(renderer, "images/opening/logo.png");

	texture->optionstex = IMG_LoadTexture(renderer, "images/menu/options.png");
	texture->menutex = IMG_LoadTexture(renderer, "images/menu/menu.png");
	texture->menurolltex = IMG_LoadTexture(renderer, "images/menu/roll.png");
	texture->creditstex = IMG_LoadTexture(renderer, "images/menu/credits.png");
	texture->highscorestex = IMG_LoadTexture(renderer, "images/menu/highscores.png");



	if (texture->backgroundtex == NULL)
	{
		fprintf(stderr, "fodeu\n%s", SDL_GetError());
	}

	font.scoretela = TTF_OpenFont("fonte.ttf", 100);
	font.scorefinal = TTF_OpenFont("fonte.ttf", 100);

}

void desenha(SDL_Renderer* renderer, Gamestate *gamestate,Texture *texture)
{	
	
	SDL_Rect salaRect = {gamestate->sala[gamestate->salaatual].x, gamestate->sala[gamestate->salaatual].y, gamestate->sala[gamestate->salaatual].w, gamestate->sala[gamestate->salaatual].h};
	SDL_RenderCopy(renderer, texture->backgroundtex,&salaRect ,NULL); 

	
	int j;
	for(j = 0; j< MAXBULLETS; j++)
	{
		if(bullet[j].on == 1)
		{
			if(gamestate->player.arma == 1)
			{
				SDL_Rect bulletRect = {bullet[j].x,bullet[j].y,15,15};	
				SDL_RenderCopy(renderer, texture->bullettex, NULL, &bulletRect);	
			}

			if(gamestate->player.arma == 2)
			{
				SDL_Rect bulletRect = {bullet[j].x,bullet[j].y,10,10};
				SDL_RenderCopy(renderer, texture->bullettex, NULL, &bulletRect);		
			}

			if(gamestate->player.arma == 3)
			{
				SDL_Rect bulletRect = {bullet[j].x,bullet[j].y,20,20};	
				SDL_RenderCopy(renderer, texture->bullettex, NULL, &bulletRect);	
			}
			
			
		}
	}
	
	int i;
	for(i = 0; i< MAXENEMIES; i++)
	{
		if(enemy[i].on == 1)
		{
			SDL_Rect enemyRect = {enemy[i].x,enemy[i].y,enemy[i].w,enemy[i].h};
			SDL_Rect enemydrawRect = {0,0,enemy[i].w,enemy[i].h};
			SDL_RenderCopyEx(renderer, texture->enemytex,&enemydrawRect,&enemyRect,enemy[i].angulo,NULL,SDL_FLIP_HORIZONTAL);
		}
	}

	int m;
	for(m = 0; m< MAXENEMIES; m++)
	{
		if(enemymedium[m].on == 1)
		{
			SDL_Rect enemymediumRect = {enemymedium[m].x,enemymedium[m].y,enemymedium[m].w,enemymedium[m].h};
			SDL_Rect enemymediumdrawRect = {0,0,enemymedium[m].w,enemymedium[m].h};
			SDL_RenderCopyEx(renderer, texture->enemymediumtex,&enemymediumdrawRect,&enemymediumRect,enemymedium[m].angulo,NULL,SDL_FLIP_HORIZONTAL);
		}
	}

	int b;
	for(b = 0; b< MAXENEMIES; b++)
	{
		if(enemyboss[b].on == 1)
		{
			SDL_Rect enemybossRect = {enemyboss[b].x,enemyboss[b].y,enemyboss[b].w,enemyboss[b].h};
			SDL_Rect enemybossdrawRect = {0,0,enemyboss[b].w/2,enemyboss[b].h/2};
			SDL_RenderCopyEx(renderer, texture->enemybosstex,&enemybossdrawRect,&enemybossRect,enemyboss[b].angulo,NULL,SDL_FLIP_HORIZONTAL);

			SDL_Rect bosslifeRect = {1266 - enemyboss[b].life,50,enemyboss[b].life , 10};
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, &bosslifeRect);
		}
	}

	int l;
	for(l = 0; l< MAXPOWERUP; l++)
	{
		if(lifeplus[l].on == 1)
		{
			SDL_Rect lifeplusRect = {lifeplus[l].x,lifeplus[l].y,lifeplus[l].w,lifeplus[l].h};
			SDL_RenderCopy(renderer, texture->lifeplustex,NULL,&lifeplusRect);
		}
	}

	int s;
	for(s = 0; s< MAXPOWERUP; s++)
	{
		if(speedplus[s].on == 1)
		{
			SDL_Rect speedplusRect = {speedplus[s].x,speedplus[s].y,speedplus[s].w,speedplus[s].h};
			SDL_RenderCopy(renderer, texture->speedplustex,NULL,&speedplusRect);
		}
	}

	int d;
	for(d = 0; d< MAXPOWERUP; d++)
	{
		if(damageplus[d].on == 1)
		{
			SDL_Rect damageplusRect = {damageplus[d].x,damageplus[d].y,damageplus[d].w,damageplus[d].h};
			SDL_RenderCopy(renderer, texture->damageplustex,NULL,&damageplusRect);
		}
	}

	int um;
	for(um = 0; um< MAXPOWERUP; um++)
	{
		if(arma1[um].on == 1)
		{
			SDL_Rect arma1Rect = {arma1[um].x,arma1[um].y,arma1[um].w,arma1[um].h};
			SDL_RenderCopy(renderer, texture->arma1tex,NULL,&arma1Rect);
		}
	}

	int dois;
	for(dois = 0; dois< MAXPOWERUP; dois++)
	{
		if(arma2[dois].on == 1)
		{
			SDL_Rect arma2Rect = {arma2[dois].x,arma2[dois].y,arma2[dois].w,arma2[dois].h};
			SDL_RenderCopy(renderer, texture->arma2tex,NULL,&arma2Rect);
		}
	}

	int tres;
	for(tres = 0; tres< MAXPOWERUP; tres++)
	{
		if(arma3[tres].on == 1)
		{
			SDL_Rect arma3Rect = {arma3[tres].x,arma3[tres].y,arma3[tres].w,arma3[tres].h};
			SDL_RenderCopy(renderer, texture->arma3tex,NULL,&arma3Rect);
		}
	}


	

	
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


	if(gamestate->sala[gamestate->salaatual].clear == 0)
	{
		SDL_RenderCopy(renderer, texture->portadowntex, NULL, &portadownRect);
		SDL_RenderCopy(renderer, texture->portalefttex, NULL, &portaleftRect);
		SDL_RenderCopy(renderer, texture->portarighttex, NULL, &portarightRect);
		SDL_RenderCopy(renderer, texture->portauptex, NULL, &portaupRect);
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


	SDL_Rect playerdrawRect = {0,0,gamestate->player.w,gamestate->player.h};
	if(gamestate->player.arma == 1)
	{
		SDL_RenderCopyEx(renderer, texture->playerw1tex,&playerdrawRect, &playerRect,gamestate->player.angulo,NULL,SDL_FLIP_HORIZONTAL);
		
	}
	if(gamestate->player.arma == 2)
	{
		SDL_RenderCopyEx(renderer, texture->playerw2tex,&playerdrawRect, &playerRect,gamestate->player.angulo,NULL,SDL_FLIP_HORIZONTAL);
		
	}
	if(gamestate->player.arma == 3)
	{
		SDL_RenderCopyEx(renderer, texture->playerw3tex,&playerdrawRect, &playerRect,gamestate->player.angulo,NULL,SDL_FLIP_HORIZONTAL);
		
	}

	
	

	if(gamestate->victory == 1)
	{
		int opacidade = 0;
		SDL_RenderPresent(renderer);
		
		while(opacidade < 255 )
		{
			
			
			SDL_SetTextureBlendMode(texture->brancotex,SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(texture->brancotex,opacidade);
			SDL_RenderCopy(renderer, texture->brancotex,NULL, 0);
			opacidade += 1;	
			SDL_Delay(10);
			
			SDL_RenderPresent(renderer);
			 
		}

		SDL_Delay(500);

		opacidade = 0;

		while(opacidade < 255 )
		{
						
			
			SDL_SetTextureBlendMode(texture->pretotex,SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(texture->pretotex,opacidade);
			SDL_RenderCopy(renderer, texture->pretotex,NULL, 0);

			opacidade += 1;	
			SDL_Delay(5);
			SDL_RenderPresent(renderer);
			
		}
	}

	
	

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	if(gamestate->victory == 0)
	{



		SDL_Rect playerlifeRect = {107,45,(gamestate->player.life *0.53) , 15};
		SDL_SetRenderDrawColor(renderer, 100, 255, 100, 255);
		SDL_RenderFillRect(renderer, &playerlifeRect);

		SDL_Rect lifebarRect = {100,25,250, 40};
		SDL_RenderCopy(renderer, texture->lifebar, NULL, &lifebarRect);

		SDL_Rect scoretelaRect = {110,680,300 , 40};
		SDL_Color branco = {255,255,255, SDL_ALPHA_OPAQUE};

		SDL_Rect howtopauseRect = {966,680,300, 32};
		SDL_RenderCopy(renderer, texture->howtopausetex, NULL, &howtopauseRect);

		char str[15];
		sprintf(str, "Pontos : %05d", gamestate->player.score);		

		SDL_Surface* scoretelaSurface = TTF_RenderText_Solid(font.scoretela,str,branco);
		
		texture->scoretela = SDL_CreateTextureFromSurface( renderer, scoretelaSurface );	

		SDL_FreeSurface(scoretelaSurface);

		SDL_RenderCopy(renderer, texture->scoretela, NULL, &scoretelaRect);

		if(gamestate->pause == 1)
		{
			SDL_RenderCopy(renderer, texture->pausetex,NULL ,NULL);
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);    


	}

}