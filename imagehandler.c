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
	texture->enemybullettex = IMG_LoadTexture(renderer, "images/game/enemybullet.png");
	texture->boom = IMG_LoadTexture(renderer, "images/game/boom.png");

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
	texture->playerw1hurttex = IMG_LoadTexture(renderer, "images/game/playerw1hurt.png");
	texture->playerw2hurttex = IMG_LoadTexture(renderer, "images/game/playerw2hurt.png");
	texture->playerw3hurttex = IMG_LoadTexture(renderer, "images/game/playerw3hurt.png");
	texture->playerw1deadtex = IMG_LoadTexture(renderer, "images/game/playerw1dead.png");


	texture->gameintrotex = IMG_LoadTexture(renderer, "images/game/historia.png");
	texture->instructionstex = IMG_LoadTexture(renderer, "images/game/instructions.png");
	texture->instructions1tex = IMG_LoadTexture(renderer, "images/game/instructions1.png");

	texture->wintex = IMG_LoadTexture(renderer, "images/gameover/win.png");
	texture->losetex = IMG_LoadTexture(renderer, "images/gameover/lose.png");

	texture->openingtex = IMG_LoadTexture(renderer, "images/opening/sdlop.png");
	texture->logotex = IMG_LoadTexture(renderer, "images/opening/logo.png");

	texture->options0tex = IMG_LoadTexture(renderer, "images/menu/options0.png");
	texture->options1tex = IMG_LoadTexture(renderer, "images/menu/options1.png");
	texture->menutex = IMG_LoadTexture(renderer, "images/menu/menu.png");
	texture->menurolltex = IMG_LoadTexture(renderer, "images/menu/roll.png");
	texture->creditstex = IMG_LoadTexture(renderer, "images/menu/credits.png");
	texture->highscoresbgtex = IMG_LoadTexture(renderer, "images/menu/highscores.png");
	texture->namescreentex = IMG_LoadTexture(renderer, "images/menu/insertname.png");

	texture->derroteochefe = IMG_LoadTexture(renderer, "images/menu/DERROTEOCHEFE.png");



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

	for(j = 0; j< MAXBULLETS; j++)
	{
		if(enemybullet[j].on == 1)
		{
			SDL_Rect enemybulletRect = {enemybullet[j].x,enemybullet[j].y,15,15};	
			SDL_RenderCopy(renderer, texture->enemybullettex, NULL, &enemybulletRect);
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


	int a;	

	
	

	

	int i;
	for(i = 0; i< MAXENEMIES; i++)
	{
		
		for(a = 0; a < 4; a++)
		{
			enemydrawRect[i][a].x = a * enemy[i].w + 3;
			enemydrawRect[i][a].y = 0;
			enemydrawRect[i][a].w = enemy[i].w;
			enemydrawRect[i][a].h = enemy[i].h;
		}

		

		if(enemy[i].move == 1)
		{
			currentenemyframeRect[i] = enemydrawRect[i][ gamestate->enemyframe/8];		
		}
		else
		{
			currentenemyframeRect[i] = enemydrawRect[i][ 2];
		}

		if(enemy[i].on == 1)
		{

			SDL_Rect enemyRect = {enemy[i].x,enemy[i].y,enemy[i].w,enemy[i].h};
			
			SDL_RenderCopyEx(renderer, texture->enemytex,&currentenemyframeRect[i],&enemyRect,enemy[i].angulo,NULL,SDL_FLIP_HORIZONTAL);
		}
		else if(enemy[i].dead == 1)
		{
			if(enemy[i].frameboom < 4)
			{


				SDL_Rect enemyboom = {enemy[i].x,enemy[i].y,enemy[i].w,enemy[i].h/1.8};
				SDL_Rect enemyboomdraw = {enemy[i].frameboom*20,0,20,20};
				SDL_RenderCopy(renderer, texture->boom, &enemyboomdraw, &enemyboom);

				if(enemy[i].cont % 8 == 0)
				{
					enemy[i].frameboom++;
				}

						
				enemy[i].cont++;	
										
			}
			else
			{
				enemy[i].dead = 0;
				enemy[i].frameboom = 0;
				enemy[i].cont = 0;
				 enemy[i].w = 0;
				 enemy[i].h = 0;
				 enemy[i].x = 0;
				 enemy[i].y = 0;
			}
		}
		
	}



	int m;
	for(m = 0; m< MAXENEMIES; m++)
	{
		
		for(a = 0; a < 4; a++)
		{
			enemymediumdrawRect[m][a].x = a * enemymedium[m].w + 3;
			enemymediumdrawRect[m][a].y = 0;
			enemymediumdrawRect[m][a].w = enemymedium[m].w;
			enemymediumdrawRect[m][a].h = enemymedium[m].h;
		}

		

		if(enemymedium[m].move == 1)
		{
			currentenemymediumframeRect[m] = enemymediumdrawRect[m][ gamestate->enemyframe/8];		
		}
		else
		{
			currentenemymediumframeRect[m] = enemymediumdrawRect[m][ 2];
		}

		if(enemymedium[m].on == 1)
		{
			SDL_Rect enemymediumRect = {enemymedium[m].x,enemymedium[m].y,enemymedium[m].w,enemymedium[m].h};
			
			SDL_RenderCopyEx(renderer, texture->enemymediumtex,&currentenemymediumframeRect[m],&enemymediumRect,enemymedium[m].angulo,NULL,SDL_FLIP_HORIZONTAL);
		}
		else if(enemymedium[m].dead == 1)
		{
			if(enemymedium[m].frameboom < 4)
			{


				SDL_Rect enemymediumboom = {enemymedium[m].x,enemymedium[m].y,enemymedium[m].w,enemymedium[m].h/1.4};
				SDL_Rect enemymediumboomdraw = {enemymedium[m].frameboom*20,0,20,20};
				SDL_RenderCopy(renderer, texture->boom, &enemymediumboomdraw, &enemymediumboom);

				if(enemymedium[m].cont % 8 == 0)
				{
					enemymedium[m].frameboom++;
				}

						
				enemymedium[m].cont++;	
										
			}
			else 
			{
				enemymedium[m].dead = 0;
				enemymedium[m].frameboom = 0;
				enemymedium[m].cont = 0;
				 enemymedium[m].w = 0;
				 enemymedium[m].h = 0;
				 enemymedium[m].x = 0;
				 enemymedium[m].y = 0;
			}
		}
		
	}

	

	int b;
	for(b = 0; b< MAXENEMIES; b++)
	{
		for(a = 0; a < 4; a++)
		{
			enemybossdrawRect[b][a].x = a * (enemyboss[b].w/2) + 3;
			enemybossdrawRect[b][a].y = 0;
			enemybossdrawRect[b][a].w = enemyboss[b].w/2;
			enemybossdrawRect[b][a].h = enemyboss[b].h/2;
		}

		

		if(enemyboss[b].move == 1)
		{
			currentenemybossframeRect[b] = enemybossdrawRect[b][ gamestate->enemyframe/8];		
		}
		else
		{
			currentenemybossframeRect[b] = enemybossdrawRect[b][ 2];
		}

		if(enemyboss[b].on == 1)
		{
			SDL_Rect enemybossRect = {enemyboss[b].x,enemyboss[b].y,enemyboss[b].w,enemyboss[b].h};
			
			SDL_RenderCopyEx(renderer, texture->enemybosstex,&currentenemybossframeRect[b],&enemybossRect,enemyboss[b].angulo,NULL,SDL_FLIP_HORIZONTAL);
			SDL_Rect bosslifeRect = {1266 - enemyboss[b].life,50,enemyboss[b].life , 10};

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, &bosslifeRect);
		}
		else if(enemyboss[b].dead == 1)
		{
			if(enemyboss[b].frameboom < 4)
			{


				SDL_Rect enemybossboom = {enemyboss[b].x-100,enemyboss[b].y-100,enemyboss[b].w*1.4,enemyboss[b].h};
				SDL_Rect enemybossboomdraw = {enemyboss[b].frameboom*20,0,20,20};
				SDL_RenderCopy(renderer, texture->boom, &enemybossboomdraw, &enemybossboom);



				if(enemyboss[b].cont % 8 == 0)
				{
					enemyboss[b].frameboom++;
				}

						
				enemyboss[b].cont++;	
										
			}
			else
			{
				enemyboss[b].dead = 0;
				enemyboss[b].frameboom = 0;
				enemyboss[b].cont = 0;
				 enemyboss[b].w = 0;
				 enemyboss[b].h = 0;
				 enemyboss[b].x = 0;
				 enemyboss[b].y = 0;
				 gamestate->victory = 1;
				 SDL_Delay(15);
			}
		}
	
		
	}


	gamestate->enemyframe++;

	if(gamestate->enemyframe / 8 >= 4)
	{
		gamestate->enemyframe = 0;	
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

	

	if(gamestate->player.life > 0)
	{
		SDL_Rect playerdrawRect[6];

		for(a = 0; a < 6; a++)
		{
			playerdrawRect[a].x = a * gamestate->player.w + 3;
			playerdrawRect[a].y = 0;
			playerdrawRect[a].w = gamestate->player.w;
			playerdrawRect[a].h = gamestate->player.h;
		}

		SDL_Rect currentplayerframeRect;

		if(gamestate->playerup == 1 || gamestate->playerdown == 1 || gamestate->playerleft == 1 || gamestate->playerright == 1 )
		{
			currentplayerframeRect = playerdrawRect[ gamestate->player.frame / 6 ];		
		}
		else
		{
			currentplayerframeRect = playerdrawRect[ 2];
		}


		if(gamestate->danocolldown > 0)
		{
			if(gamestate->danocolldown % 30 > 15)
			{
				if(gamestate->player.arma == 1)
				{
					SDL_SetTextureBlendMode(texture->playerw1tex,SDL_BLENDMODE_BLEND);
					SDL_SetTextureAlphaMod(texture->playerw1tex,gamestate->player.life / 2);

					SDL_RenderCopyEx(renderer, texture->playerw1hurttex,&currentplayerframeRect, &playerRect,gamestate->player.angulo,NULL,SDL_FLIP_HORIZONTAL);
					
					SDL_RenderCopyEx(renderer, texture->playerw1tex,&currentplayerframeRect, &playerRect,gamestate->player.angulo,NULL,SDL_FLIP_HORIZONTAL);
					
				}
				if(gamestate->player.arma == 2)
				{
					SDL_SetTextureBlendMode(texture->playerw2tex,SDL_BLENDMODE_BLEND);
					SDL_SetTextureAlphaMod(texture->playerw2tex,gamestate->player.life / 2);

					SDL_RenderCopyEx(renderer, texture->playerw2hurttex,&currentplayerframeRect, &playerRect,gamestate->player.angulo,NULL,SDL_FLIP_HORIZONTAL);
					
					SDL_RenderCopyEx(renderer, texture->playerw2tex,&currentplayerframeRect, &playerRect,gamestate->player.angulo,NULL,SDL_FLIP_HORIZONTAL);
					
					
				}
				if(gamestate->player.arma == 3)
				{
					SDL_SetTextureBlendMode(texture->playerw3tex,SDL_BLENDMODE_BLEND);
					SDL_SetTextureAlphaMod(texture->playerw3tex,gamestate->player.life / 2);

					SDL_RenderCopyEx(renderer, texture->playerw3hurttex,&currentplayerframeRect, &playerRect,gamestate->player.angulo,NULL,SDL_FLIP_HORIZONTAL);
					
					SDL_RenderCopyEx(renderer, texture->playerw3tex,&currentplayerframeRect, &playerRect,gamestate->player.angulo,NULL,SDL_FLIP_HORIZONTAL);
					
					
				}
			}
		}

		if(gamestate->danocolldown == 0)
		{
			if(gamestate->player.arma == 1)
			{
				SDL_SetTextureBlendMode(texture->playerw1tex,SDL_BLENDMODE_BLEND);
					SDL_SetTextureAlphaMod(texture->playerw1tex,gamestate->player.life / 2);

					SDL_RenderCopyEx(renderer, texture->playerw1hurttex,&currentplayerframeRect, &playerRect,gamestate->player.angulo,NULL,SDL_FLIP_HORIZONTAL);
					
					SDL_RenderCopyEx(renderer, texture->playerw1tex,&currentplayerframeRect, &playerRect,gamestate->player.angulo,NULL,SDL_FLIP_HORIZONTAL);
				
			}
			if(gamestate->player.arma == 2)
			{
				SDL_SetTextureBlendMode(texture->playerw2tex,SDL_BLENDMODE_BLEND);
					SDL_SetTextureAlphaMod(texture->playerw2tex,gamestate->player.life / 2);

					SDL_RenderCopyEx(renderer, texture->playerw2hurttex,&currentplayerframeRect, &playerRect,gamestate->player.angulo,NULL,SDL_FLIP_HORIZONTAL);
					
					SDL_RenderCopyEx(renderer, texture->playerw2tex,&currentplayerframeRect, &playerRect,gamestate->player.angulo,NULL,SDL_FLIP_HORIZONTAL);
				
			}
			if(gamestate->player.arma == 3)
			{
				SDL_SetTextureBlendMode(texture->playerw3tex,SDL_BLENDMODE_BLEND);
					SDL_SetTextureAlphaMod(texture->playerw3tex,gamestate->player.life / 2);

					SDL_RenderCopyEx(renderer, texture->playerw3hurttex,&currentplayerframeRect, &playerRect,gamestate->player.angulo,NULL,SDL_FLIP_HORIZONTAL);
					
					SDL_RenderCopyEx(renderer, texture->playerw3tex,&currentplayerframeRect, &playerRect,gamestate->player.angulo,NULL,SDL_FLIP_HORIZONTAL);
				
			}
		}
	}


	if(gamestate->player.life <= 0)
	{
		if(gamestate->player.framedead < 4)
			{


				SDL_Rect playerdead = {gamestate->player.x,gamestate->player.y,gamestate->player.w,gamestate->player.h};
				SDL_Rect playerdeaddraw;
				playerdeaddraw.x = gamestate->player.framedead * gamestate->player.w + 3;
				playerdeaddraw.y = 0;
				playerdeaddraw.w = gamestate->player.w;
				playerdeaddraw.h = gamestate->player.h;

				SDL_RenderCopyEx(renderer, texture->playerw1deadtex,&playerdeaddraw, &playerdead,gamestate->player.angulo,NULL,SDL_FLIP_HORIZONTAL);

				if(gamestate->player.cont % 10 == 0)
				{

					gamestate->player.framedead++;
					printf("%d\n",gamestate->player.framedead);
				}

						
				gamestate->player.cont++;	
										
			}
			else
			{
			
				gamestate->player.defeat = 1;
				
			}
	}
	

	

	gamestate->player.frame++;

	

	if(gamestate->player.frame / 6 >= 6)
	{
		gamestate->player.frame = 0;	
	}


	if(gamestate->player.bombpressed == 1)
	{
		int opacidade = 0;
		SDL_RenderPresent(renderer);
		
		while(opacidade < 170 )
		{
			
			
			SDL_SetTextureBlendMode(texture->brancotex,SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(texture->brancotex,opacidade);
			SDL_RenderCopy(renderer, texture->brancotex,NULL, 0);
			opacidade += 1;	
			
			
			SDL_RenderPresent(renderer);
			 
		}
		SDL_Delay(50);
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
			SDL_Delay(5);
			
			SDL_RenderPresent(renderer);
			 
		}

		SDL_Delay(50);

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



		SDL_Rect playerlifeRect = {107,45,(gamestate->player.life *0.53) , 20};
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderFillRect(renderer, &playerlifeRect);

		SDL_Rect bombbarRect = {107,70,(gamestate->player.bombbar ) , 10};
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderFillRect(renderer, &bombbarRect);

		SDL_Rect lifebarRect = {100,20,250, 68};
		SDL_RenderCopy(renderer, texture->lifebar, NULL, &lifebarRect);

		SDL_Rect howtopauseRect = {966,680,300, 32};
		SDL_RenderCopy(renderer, texture->howtopausetex, NULL, &howtopauseRect);

		SDL_Rect scoretelaRect = {110,680,300 , 40};
		SDL_Color branco = {255,255,255, SDL_ALPHA_OPAQUE};
		char playerscore[15];
		sprintf(playerscore, "PONTOS : %05d", gamestate->player.score);	
		SDL_Surface* scoretelaSurface = TTF_RenderText_Solid(font.scoretela,playerscore,branco);		
		texture->scoretela = SDL_CreateTextureFromSurface( renderer, scoretelaSurface );	
		SDL_FreeSurface(scoretelaSurface);
		SDL_RenderCopy(renderer, texture->scoretela, NULL, &scoretelaRect);



		if(gamestate->player.bombbar == 100)
		{
			SDL_Rect pressspace = {360,47,170 , 30};			
			SDL_Surface* pressspacesurface = TTF_RenderText_Solid(font.scoretela,"PRESSIONE SPACE",branco);		
			texture->pressspace = SDL_CreateTextureFromSurface( renderer, pressspacesurface );	
			SDL_FreeSurface(pressspacesurface);
			SDL_RenderCopy(renderer, texture->pressspace, NULL, &pressspace);
		}


		if(gamestate->pause == 1)
		{
			SDL_RenderCopy(renderer, texture->pausetex,NULL ,NULL);
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);    


	}

}