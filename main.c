#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "main.h"
#include "logic.h"
#include "states.h"





void init (Gamestate *);

void closing(SDL_Window**,SDL_Renderer**);

int recebeImput(SDL_Event *, Gamestate *,APPSTATE*);

void initwindow(SDL_Window**,SDL_Renderer**);

void salahandler(Gamestate*);

int gameintro(SDL_Window** window, SDL_Renderer**renderer,SDL_Event * event, Gamestate *gamestate,APPSTATE*state);

void gameended();


void audioinit()
{
	Mix_OpenAudio(11025, MIX_DEFAULT_FORMAT, 1, 4096);
	Mix_VolumeMusic(128);
	Mix_Volume(-1,128);
	Mix_AllocateChannels(30);

	music.menu = Mix_LoadMUS("sounds/menu.wav");
	music.boss = Mix_LoadMUS("sounds/boss.wav");
	music.game = Mix_LoadMUS("sounds/game.mp3");
	music.lose = Mix_LoadMUS("sounds/lose.mp3");
	music.win = Mix_LoadMUS("sounds/win.mp3");
	sound.arma1 = Mix_LoadWAV("sounds/arma1.wav");
	sound.arma2 = Mix_LoadWAV("sounds/arma2.wav");
	sound.arma3 = Mix_LoadWAV("sounds/arma3.wav");
	sound.damage = Mix_LoadWAV("sounds/damage.wav");
	sound.life = Mix_LoadWAV("sounds/life.wav");
	sound.speed = Mix_LoadWAV("sounds/speed.wav");
	sound.playerdano = Mix_LoadWAV("sounds/playerdano.wav");
	sound.reload = Mix_LoadWAV("sounds/reload.wav");
	sound.enemydano = Mix_LoadWAV("sounds/enemydano.wav");
	sound.menuroll = Mix_LoadWAV("sounds/menuroll.wav");
	sound.menuenter = Mix_LoadWAV("sounds/menuenter.wav");
	sound.boom = Mix_LoadWAV("sounds/boom.wav");


}



int main(int argc, char const *argv[])
{
	
	audioinit();
	
	array.n = 0;
	

	APPSTATE state = OPENING;
	srand(time(0));



	Gamestate gamestate;
	SDL_Window *window = NULL ; 
	SDL_Renderer *renderer = NULL ;

	gamestate.player.name[0] = '\0';
	gamestate.player.score = 0;
	gamestate.gamemode = 0;
	gamestate.musicvolume = 128;
	gamestate.soundvolume = 128;
	

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

					opening(&window,&renderer,&event,&gamestate,&state);

					state = MENU;
					break;
				}
				case MENU:
				{
					if(!Mix_PlayingMusic())
					Mix_FadeInMusic(music.menu, -1, 500);
					gamestate.menuroll = 0;
					fadeinmenu(&window,&renderer);
					int decide = 0;

					while(decide == 0)
					{
						decide = recebeImput(&event,&gamestate,&state);	
						desenhamenu(&renderer,&gamestate);
						if(gamestate.menuroll > 4)
						{
							gamestate.menuroll = 0;
						}
						if(gamestate.menuroll < 0)
						{
							gamestate.menuroll = 4;
						}
					}

					switch(gamestate.menuroll)
					{
						case 0:
							state = NEWGAME;
							break;
						case 1:
							state = HIGHSCORE; 
							break;
						case 2:
							state = CREDITOS;
							break;
						case 3:
							state = OPTIONS;
							break;
						case 4: 
							Mix_FadeOutMusic(200);
							state = EXIT;
							break;
					}
					//Mix_FadeOutMusic(500);
					fadeoutmenu(&window,&renderer);
					

					break;
						
				}
				case OPTIONS:
				{
					
					int decide = 0;
					gamestate.optionsroll = 0;

					while(decide == 0)
					{
						Mix_VolumeMusic(gamestate.musicvolume);
						Mix_Volume(-1,gamestate.soundvolume);
						decide = recebeImput(&event,&gamestate,&state);	
						options(&renderer,&gamestate);
						if(gamestate.optionsroll > 3)
						{
							gamestate.optionsroll = 0;
						}
						if(gamestate.optionsroll < 0)
						{
							gamestate.optionsroll = 3;
						}

						
						//state = MENU;
					}
						
					break;
				}
				case HIGHSCORE:
				{
					int decide = 0;

					

					while(decide == 0)
					{
						highscores(&window,&renderer,&gamestate);
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
					Mix_FadeOutMusic(200);
					gamestate.intro = 1;
					
					
					Mix_FadeInMusic(music.game, -1, 500);
					

					init(&gamestate);


					int running = 1;

					gamestate.mute = 0;
					Mix_ResumeMusic();
					Mix_Resume(-1);
					

					running = gameintro(&window,&renderer,&event,&gamestate,&state);

					while(running == 1)
					{
						//printf("life: %d\n",gamestate.player.life);

						Mix_VolumeMusic(gamestate.musicvolume);
						Mix_Volume(-1,gamestate.soundvolume);
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
						
							

						
						if(gamestate.player.life <= 0)
						{						
							state = GAMEOVERLOSE;
							running = 0;
							gamestate.victory = -1;
						}

						if(gamestate.victory == 1)
						{
							state = GAMEOVERWIN;
							Mix_FadeOutMusic(100);
							running = 0;
							//("yeah");
						}
						else;

						desenha(renderer,&gamestate,&texture);
							
						//printf("estado: %d\n",gamestate.sala[BOSS].clear );

						fim = SDL_GetTicks();

						if (fim - inicio < 1000/60)
							SDL_Delay(1000/60-(fim-inicio));

						

					}
					gamestate.mute = 0;
					Mix_Resume(-1);
					Mix_ResumeMusic();
					Mix_FadeOutMusic(500);
					

					

					break;
				}
				case GAMEOVERWIN:
				{	
					Mix_FadeInMusic(music.win, -1, 2000);

					int opacidade = 0;				

					int go = 0;

				    int historiaW = 1366;
				    int historiaH = 1691;
				    int rollup = 768;

				    SDL_Rect historiaRect;				    

					


					while(rollup > (historiaH * -1 ) && go == 0)
					{
						historiaRect.x = 0;
						historiaRect.y = rollup;
						historiaRect.w = historiaW;
						historiaRect.h = historiaH;


						SDL_RenderCopy(renderer, texture.gameintrotex,NULL, &historiaRect);

						go = recebeImput(&event,&gamestate,&state);

						rollup -= 1;
						SDL_Delay(10);

						SDL_RenderPresent(renderer);
						SDL_RenderClear(renderer);

		
					}

					
					SDL_RenderCopy(renderer, texture.wintex,NULL, 0);
					SDL_RenderPresent(renderer);



					SDL_Delay(1000);
					SDL_RenderClear(renderer); 


					
					char *nome_arquivo = "recordes.dat";

					if((arquivos.p_arquivo = fopen(nome_arquivo, "r")) != NULL)
				    {
				        fread(&array, sizeof(ARRAY), 1, arquivos.p_arquivo);
				        fclose(arquivos.p_arquivo);
				    }

					RECORDE rec1;

					SDL_Color branco = {255,255,255, SDL_ALPHA_OPAQUE};

					int done = 0;

					SDL_StartTextInput();

					while(done == 0)
					{
						done = recebeImput(&event,&gamestate,&state);

						SDL_RenderCopy(renderer, texture.namescreentex,NULL, 0);

						SDL_Rect scoretelaRect = {(1366/2) - 90,200,180 , 80};						
						char playerscore[15];
						sprintf(playerscore, "%05d", gamestate.player.score);	
						SDL_Surface* scoretelaSurface = TTF_RenderText_Solid(font.scoretela,playerscore,branco);		
						texture.scoretela = SDL_CreateTextureFromSurface( renderer, scoretelaSurface );	
						SDL_FreeSurface(scoretelaSurface);
						SDL_RenderCopy(renderer, texture.scoretela, NULL, &scoretelaRect); 
						

						SDL_Rect insertnameRect = {(1366/2)-(strlen(gamestate.player.name)*15/2), 400, 15 * strlen(gamestate.player.name)  , 40};													
						SDL_Surface* insertnameSurface = TTF_RenderText_Solid(font.scoretela,gamestate.player.name,branco);	
						texture.insertnametex = SDL_CreateTextureFromSurface( renderer, insertnameSurface );	
						SDL_FreeSurface(insertnameSurface);
						SDL_RenderCopy(renderer, texture.insertnametex, NULL, &insertnameRect);
						SDL_RenderPresent(renderer);
						SDL_RenderClear(renderer); 
					}

					if(done < 0)
					{
						break;
					}

					SDL_StopTextInput();
    				//scanf("%s",gamestate.player.name);

				    strcpy(rec1.nome, gamestate.player.name);

				    //rec1.nome[strlen(rec1.nome) - 1] = '\0';

				   	rec1.pontuacao = gamestate.player.score;

				    inserehighscore(&array, rec1);

				    

				     if((arquivos.p_arquivo = fopen(nome_arquivo, "w")) == NULL)
				    {
				        perror("fopen:");
				        return 0;
				    }

				    fwrite(&array, sizeof(ARRAY), 1, arquivos.p_arquivo);
				    fclose(arquivos.p_arquivo);

				    

					SDL_Delay(100);
					SDL_RenderClear(renderer);

					state = HIGHSCORE;


					






					Mix_FadeOutMusic(500);

					break;
				}
				case GAMEOVERLOSE:
				{
					Mix_FadeInMusic(music.lose, -1, 200);

					int decide = 0;

					int opacidade = 0;

					SDL_RenderPresent(renderer);
					
					while(opacidade < 255 )
					{
						
						
						SDL_SetTextureBlendMode(texture.losetex,SDL_BLENDMODE_BLEND);
						SDL_SetTextureAlphaMod(texture.losetex,opacidade);
						SDL_RenderCopy(renderer, texture.losetex,NULL, 0);
						opacidade += 1;	
						SDL_Delay(5);
						
						SDL_RenderPresent(renderer);
						 
					}

					

					char *nome_arquivo = "recordes.dat";

					if((arquivos.p_arquivo = fopen(nome_arquivo, "r")) != NULL)
				    {
				        fread(&array, sizeof(ARRAY), 1, arquivos.p_arquivo);
				        fclose(arquivos.p_arquivo);
				    }

					RECORDE rec1;

					SDL_Color branco = {255,255,255, SDL_ALPHA_OPAQUE};

					int done = 0;

					SDL_StartTextInput();

					while(done == 0)
					{
						done = recebeImput(&event,&gamestate,&state);

						SDL_RenderCopy(renderer, texture.namescreentex,NULL, 0);

						SDL_Rect scoretelaRect = {(1366/2) - 90,200,180 , 80};						
						char playerscore[15];
						sprintf(playerscore, "%05d", gamestate.player.score);	
						SDL_Surface* scoretelaSurface = TTF_RenderText_Solid(font.scoretela,playerscore,branco);		
						texture.scoretela = SDL_CreateTextureFromSurface( renderer, scoretelaSurface );	
						SDL_FreeSurface(scoretelaSurface);
						SDL_RenderCopy(renderer, texture.scoretela, NULL, &scoretelaRect); 
						

						SDL_Rect insertnameRect = {(1366/2)-(strlen(gamestate.player.name)*15/2), 400, 15 * strlen(gamestate.player.name)  , 40};													
						SDL_Surface* insertnameSurface = TTF_RenderText_Solid(font.scoretela,gamestate.player.name,branco);	
						texture.insertnametex = SDL_CreateTextureFromSurface( renderer, insertnameSurface );	
						SDL_FreeSurface(insertnameSurface);
						SDL_RenderCopy(renderer, texture.insertnametex, NULL, &insertnameRect);
						SDL_RenderPresent(renderer);
						SDL_RenderClear(renderer); 
					}

					if(done < 0)
					{
						break;
					}

					SDL_StopTextInput();
    				//scanf("%s",gamestate.player.name);

				    strcpy(rec1.nome, gamestate.player.name);

				    //rec1.nome[strlen(rec1.nome) - 1] = '\0';

				   	rec1.pontuacao = gamestate.player.score;

				    inserehighscore(&array, rec1);

				    

				     if((arquivos.p_arquivo = fopen(nome_arquivo, "w")) == NULL)
				    {
				        perror("fopen:");
				        return 0;
				    }

				    fwrite(&array, sizeof(ARRAY), 1, arquivos.p_arquivo);
				    fclose(arquivos.p_arquivo);

				    

					SDL_Delay(100);
					SDL_RenderClear(renderer);

					state = HIGHSCORE;


					






					Mix_FadeOutMusic(500);

					break;
				}
				case EXIT:
				{
					Mix_FreeMusic(music.menu);
					gameended();


					SDL_DestroyRenderer(renderer);

					if(renderer != NULL)
					{
						puts("erro ao destruir");
						SDL_GetError();
					}

					closing(&window,&renderer);
					go = 0;
					return 0;
				}
			}
		
	}
		
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
					gamestate->player.x = gamestate->sala[SALA3].portaleft.w - gamestate->sala[SALA3].portaleft.x;
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
					gamestate->player.y = gamestate->sala[SALA4].portaleft.y + 1;
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
					Mix_FadeInMusic(music.boss, -1, 200);
					gamestate->salaatual = BOSS;
					gamestate->player.x = gamestate->sala[BOSS].portaleft.w - gamestate->sala[BOSS].portaleft.x + 2;
					gamestate->player.y = gamestate->sala[BOSS].portaleft.y + 50 + 3;
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
					gamestate->player.x = gamestate->sala[BONUS].portaleft.w - gamestate->sala[BONUS].portaleft.x + 2;
					gamestate->player.y = gamestate->sala[BONUS].portaleft.y + 50 + 3;
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
			
			if(gamestate->sala[gamestate->salaatual].clear == 1)
		    {	   	
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

    gamestate->player.w = 60;
    gamestate->player.h = 92;
    gamestate->player.x = gamestate->ScreenW/2 - gamestate->player.w/2 +1;
    gamestate->player.y = gamestate->ScreenH/2 - gamestate->player.h/2 ;
    gamestate->player.life = 510;
    gamestate->player.score = 0;
    gamestate->player.speed = 4;
    gamestate->playerup = 0;
    gamestate->playerdown = 0;
    gamestate->playerleft = 0;
    gamestate->playerright = 0;
    gamestate->player.arma = 1;
    gamestate->player.damageplus = 0;
    gamestate->player.frame = 0;
    gamestate->player.name[0] = '\0';
	gamestate->player.score = 0;
	gamestate->player.bombbar = 0;
	gamestate->player.bombpressed = 0;


    

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
			    gamestate->sala[gamestate->salaatual].portadown.x = 466;
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
			    gamestate->sala[gamestate->salaatual].portaup.x = 470;
			    gamestate->sala[gamestate->salaatual].portaup.y = -2;
			    gamestate->sala[gamestate->salaatual].portaup.w = 356;
			    gamestate->sala[gamestate->salaatual].portaup.h = 100;
			    gamestate->sala[gamestate->salaatual].portadown.x = 0;
			    gamestate->sala[gamestate->salaatual].portadown.y = 0;
			    gamestate->sala[gamestate->salaatual].portadown.w = 0;
			    gamestate->sala[gamestate->salaatual].portadown.h = 0;
			    gamestate->sala[gamestate->salaatual].portaleft.x = -2;
			    gamestate->sala[gamestate->salaatual].portaleft.y = 255;
			    gamestate->sala[gamestate->salaatual].portaleft.w = 100;
			    gamestate->sala[gamestate->salaatual].portaleft.h = 252;
			    gamestate->sala[gamestate->salaatual].portaright.x = 1266;
			    gamestate->sala[gamestate->salaatual].portaright.y = 250;
			    gamestate->sala[gamestate->salaatual].portaright.w = 100;
			    gamestate->sala[gamestate->salaatual].portaright.h = 260;
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
			    gamestate->sala[gamestate->salaatual].portaleft.x = -2;
			    gamestate->sala[gamestate->salaatual].portaleft.y = 255;
			    gamestate->sala[gamestate->salaatual].portaleft.w = 100;
			    gamestate->sala[gamestate->salaatual].portaleft.h = 252;
			    gamestate->sala[gamestate->salaatual].portaright.x = 0;
			    gamestate->sala[gamestate->salaatual].portaright.y = 0;
			    gamestate->sala[gamestate->salaatual].portaright.w = 0;
			    gamestate->sala[gamestate->salaatual].portaright.h = 0;
			    break;
			case BONUS:
				gamestate->sala[gamestate->salaatual].x = 1366 * 2;
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
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasytospawn = 20;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymediumtospawn = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhardtospawn = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemybosstospawn = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasy = 20;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymedium = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhard = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyboss = 0;
			    	gamestate->sala[gamestate->salaatual].clear = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyeasyleft = 20;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemymediumleft = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemyhardleft = 0;
			    	gamestate->sala[gamestate->salaatual].wave[i].enemybossleft = 0;
			    }
			    gamestate->sala[gamestate->salaatual].portaup.x = 0;
			    gamestate->sala[gamestate->salaatual].portaup.y = 0;
			    gamestate->sala[gamestate->salaatual].portaup.w = 0;
			    gamestate->sala[gamestate->salaatual].portaup.h = 0;
			    gamestate->sala[gamestate->salaatual].portadown.x = 0;
			    gamestate->sala[gamestate->salaatual].portadown.y = 0;
			    gamestate->sala[gamestate->salaatual].portadown.w = 0;
			    gamestate->sala[gamestate->salaatual].portadown.h = 0;
			    gamestate->sala[gamestate->salaatual].portaleft.x = -2;
			    gamestate->sala[gamestate->salaatual].portaleft.y = 255;
			    gamestate->sala[gamestate->salaatual].portaleft.w = 100;
			    gamestate->sala[gamestate->salaatual].portaleft.h = 252;
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
	gamestate->danocolldown = 0;

	gamestate->enemyframe = 0;


    gamestate->mousex = 600;
    gamestate->mousey = 600;

    
    for(i = 0; i < MAXENEMIES; i++)
    {
   		enemy[i].on = 0;
   		enemy[i].frameboom = 0;
		enemy[i].cont = 0;
		enemy[i].dead = 0;

    }

   	for(i = 0; i < MAXENEMIES; i++)
   	{
   		enemymedium[i].on = 0;
   		enemymedium[i].frameboom = 0;
		enemymedium[i].cont = 0;
		enemymedium[i].dead = 0;
		enemymedium[i].rof = 40;

    }

   	for(i = 0; i < MAXENEMIES; i++)
   	{
   		enemyboss[i].on = 0;
   		enemyboss[i].frameboom = 0;
		enemyboss[i].cont = 0;
		enemyboss[i].dead = 0;

    }

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


    SDL_DestroyWindow(*window);
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();

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
						gamestate->menuroll = 4;

						return 1;
					}
					if(event->type == SDL_KEYDOWN)
					{
						if(SDLK_UP == event->key.keysym.sym) 
						{
				            gamestate->menuroll -= 1;
				            Mix_PlayChannel(-1, sound.menuroll, 0);
				            return 0;
						}
				        if(SDLK_DOWN == event->key.keysym.sym) 
				        {
				            gamestate->menuroll += 1;
				            Mix_PlayChannel(-1, sound.menuroll, 0);
				            return 0;
				        }
				        if(SDLK_RETURN == event->key.keysym.sym) 
				        {
				        	Mix_PlayChannel(-1, sound.menuenter, 0);
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

					if(gamestate->optionsroll == 0)
					{
						if(event->type == SDL_KEYDOWN)
						{
							if(SDLK_LEFT == event->key.keysym.sym) 
							{
								Mix_PlayChannel(-1, sound.menuroll, 0);
					            gamestate->musicvolume -= 5;
					            if(gamestate->musicvolume <= 0)
					            {
					            	gamestate->musicvolume = 0;
					            }
					            
					            return 0;
							}
					        if(SDLK_RIGHT == event->key.keysym.sym) 
					        {
					        	Mix_PlayChannel(-1, sound.menuroll, 0);
					            gamestate->musicvolume += 5;
					            if(gamestate->musicvolume >= 128)
					            {
					            	gamestate->musicvolume = 128;
					            }
					            
					            return 0;
					        }
					    }
					}
					if(gamestate->optionsroll == 1)
					{
						if(event->type == SDL_KEYDOWN)
						{

							if(SDLK_LEFT == event->key.keysym.sym) 
							{
								Mix_PlayChannel(-1, sound.menuroll, 0);
					            gamestate->soundvolume -= 5;
					            if(gamestate->soundvolume <= 0)
					            {
					            	gamestate->soundvolume = 0;
					            }
					            
					            return 0;
							}
					        if(SDLK_RIGHT == event->key.keysym.sym) 
					        {
					        	Mix_PlayChannel(-1, sound.menuroll, 0);
					            gamestate->soundvolume += 5;
					            if(gamestate->soundvolume >= 128)
					            {
					            	gamestate->soundvolume = 128;
					            }
					            
					            return 0;
					        }
					    }
					}
					if(gamestate->optionsroll == 2)
					{
						if(event->type == SDL_KEYDOWN)
						{
							if(SDLK_LEFT == event->key.keysym.sym) 
							{
								Mix_PlayChannel(-1, sound.menuroll, 0);
					            if(gamestate->gamemode == 1)
					            {
					            	gamestate->gamemode = 0;
					            }
					            else if(gamestate->gamemode == 0)
					            {
					            	gamestate->gamemode = 1;
					            }
					            
					            
					            return 0;
							}
					        if(SDLK_RIGHT == event->key.keysym.sym) 
					        {
					        	Mix_PlayChannel(-1, sound.menuroll, 0);
					            if(gamestate->gamemode == 1)
					            {
					            	gamestate->gamemode = 0;
					            }
					            else if(gamestate->gamemode == 0)
					            {
					            	gamestate->gamemode = 1;
					            }
					            
					            return 0;
					        }
					    }
					}
					if(gamestate->optionsroll == 3)
					{
						if(SDLK_RETURN == event->key.keysym.sym) 
				        {
				        	Mix_PlayChannel(-1, sound.menuenter, 0);
				        	*state = MENU;
				            return 1;
				        
				        }
					}
						
				    if(event->type == SDL_KEYDOWN)
					{
						if(SDLK_UP == event->key.keysym.sym) 
						{
							Mix_PlayChannel(-1, sound.menuroll, 0);
				            gamestate->optionsroll -= 1;
				            
				            return 0;
						}
				        if(SDLK_DOWN == event->key.keysym.sym) 
				        {
				        	Mix_PlayChannel(-1, sound.menuroll, 0);
				            gamestate->optionsroll += 1;
				            
				            return 0;
				        }
				        if(SDLK_ESCAPE == event->key.keysym.sym) 
				        {
				        	Mix_PlayChannel(-1, sound.menuenter, 0);
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
						if(SDLK_RETURN == event->key.keysym.sym) 
				        {
				        	Mix_PlayChannel(-1, sound.menuenter, 0);
				        	*state = MENU;
				            return 1;
				        
				        }
						
				        if(SDLK_ESCAPE == event->key.keysym.sym) 
				        {
				        	Mix_PlayChannel(-1, sound.menuenter, 0);
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
						if(SDLK_RETURN == event->key.keysym.sym) 
				        {
				        	Mix_PlayChannel(-1, sound.menuenter, 0);
				        	*state = MENU;
				            return 1;
				        
				        }
						
				        if(SDLK_ESCAPE == event->key.keysym.sym) 
				        {
				        	Mix_PlayChannel(-1, sound.menuenter, 0);
				            *state = MENU;
				            return 1;
				        }
				    }
					break;
				}
				case NEWGAME:
				{	

					if(gamestate->intro == 1)
					{
						if(event->type == SDL_QUIT)
						{
							*state = EXIT;
							return -1;
						}
						if(event->type == SDL_KEYDOWN)
						{
							

					        if(SDLK_RETURN == event->key.keysym.sym)
							{
								//gamestate->intro = 0;
								return 1;
							}
							if(SDLK_ESCAPE == event->key.keysym.sym)
							{
								*state = MENU;
								return -1;
							}
						}
					}
					else
					{

						if(event->type == SDL_QUIT)
						{
							*state = EXIT;
							return 1;
						}
						if(gamestate->gamemode == 0)
						{
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

						        if(SDLK_SPACE == event->key.keysym.sym)
								{
									gamestate->player.bombpressed = 1;
								}



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

						        if(SDLK_SPACE == event->key.keysym.sym)
								{
									gamestate->player.bombpressed = 0;
								}
						    }
						}

						else if(gamestate->gamemode == 1)
						{	
							if(event->type == SDL_KEYDOWN)
							{
								if(SDLK_DOWN == event->key.keysym.sym) 
						           gamestate->playerdown = 1; 
						        else if(SDLK_UP == event->key.keysym.sym) 
						            gamestate->playerup = 1;
						        if(SDLK_LEFT == event->key.keysym.sym) 
						            gamestate->playerleft = 1;
						        else if(SDLK_RIGHT == event->key.keysym.sym) 
						            gamestate->playerright = 1;
						        

						        if(SDLK_s == event->key.keysym.sym) 
						           gamestate->player.down = 1; 
						        if(SDLK_w == event->key.keysym.sym) 
						            gamestate->player.up = 1;
						        if(SDLK_a == event->key.keysym.sym) 
						            gamestate->player.left = 1;
						        if(SDLK_d == event->key.keysym.sym) 
						            gamestate->player.right = 1;

						        if(SDLK_SPACE == event->key.keysym.sym)
								{
									gamestate->player.bombpressed = 1;
								}

								if(SDLK_ESCAPE == event->key.keysym.sym)
								{
									*state = MENU;
									return 1;
								}
							}
							

							if(event->type == SDL_KEYUP)
							{
						        if(SDLK_DOWN == event->key.keysym.sym) 
						            gamestate->playerdown = 0;
						        else if(SDLK_UP == event->key.keysym.sym) 
						            gamestate->playerup = 0;
						        if(SDLK_LEFT == event->key.keysym.sym) 
						           	gamestate->playerleft = 0;
						        else if(SDLK_RIGHT == event->key.keysym.sym) 
						            gamestate->playerright = 0;

						        if(SDLK_s == event->key.keysym.sym) 
						           gamestate->player.down = 0; 
						        if(SDLK_w == event->key.keysym.sym) 
						            gamestate->player.up = 0;
						        if(SDLK_a == event->key.keysym.sym) 
						            gamestate->player.left = 0;
						        if(SDLK_d == event->key.keysym.sym) 
						            gamestate->player.right = 0;

						        if(SDLK_SPACE == event->key.keysym.sym)
								{
									gamestate->player.bombpressed = 0;
								}									
						   
							}
							
						}

					    if(gamestate->pause == 0)
						{
							if(event->type == SDL_KEYDOWN)
							{
								
								if(SDLK_p == event->key.keysym.sym)
								{
									gamestate->pause = 1;
									SDL_Delay(50);
									
									////("pra pausar");
								}	
							}
							

						}
						else if(gamestate->pause == 1)
						{
							if(event->type == SDL_KEYDOWN)
							{
								if(SDLK_p == event->key.keysym.sym)
								{
									gamestate->pause = 0;
									SDL_Delay(50);
									
									////("pra retornar");
								}
								else if(SDLK_r == event->key.keysym.sym)
								{
									*state = NEWGAME;
									return 1;
								}
								else if(SDLK_m == event->key.keysym.sym)
								{	
									int volaux;

									if(gamestate->mute == 0)
									{
										volaux = gamestate->soundvolume;
										gamestate->mute = 1;
										
										gamestate->soundvolume = 0;
										printf("volaux %d\n",volaux );
										Mix_PauseMusic();
									}
									else if(gamestate->mute == 1)
									{

										gamestate->soundvolume = 128;
										gamestate->mute = 0;
										printf("volume %d\n",gamestate->soundvolume );
										Mix_Resume(-1);
										Mix_ResumeMusic();

									}

								}
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
								return -1;

								break;

							case SDL_TEXTINPUT :

								if(strlen(gamestate->player.name) <= 11)
								{
									strcat(gamestate->player.name, event->text.text);
								}
								
								
								return 0;
								break;

							case SDL_KEYDOWN :
								if(SDLK_BACKSPACE == event->key.keysym.sym) 
						        {
						        	gamestate->player.name[strlen(gamestate->player.name) - 1] = '\0';
						            return 0;
						      	}

								if(SDLK_RETURN == event->key.keysym.sym) 
						        {
						        	
						            return 1;
						      	}
						        break;						
						}
					
					break;
				}
				case GAMEOVERLOSE:
				{
						switch (event->type) 
						{
							case SDL_QUIT:	
								
								*state = EXIT;	
								return -1;

								break;

							case SDL_TEXTINPUT :

								if(strlen(gamestate->player.name) <= 11)
								{
									strcat(gamestate->player.name, event->text.text);
								}
								
								
								return 0;
								break;

							case SDL_KEYDOWN :
								if(SDLK_BACKSPACE == event->key.keysym.sym) 
						        {
						        	gamestate->player.name[strlen(gamestate->player.name) - 1] = '\0';
						            return 0;
						      	}

								if(SDLK_RETURN == event->key.keysym.sym) 
						        {
						        	
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
            								0);
        	SDL_RenderSetLogicalSize(*renderer, ScreenW, ScreenH);
        }
    }
    TTF_Init(); // em nome de Odin
    Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
}


int gameintro(SDL_Window** window, SDL_Renderer**renderer,SDL_Event * event, Gamestate *gamestate,APPSTATE*state)
{
	int opacidade = 0;

    int go = 0;

    int historiaW = 1366;
    int historiaH = 1691;
    int rollup = 600;

    SDL_Rect historiaRect;


	while(rollup > (historiaH * -1 ) && go == 0)
	{
		

		historiaRect.x = 0;
		historiaRect.y = rollup;
		historiaRect.w = historiaW;
		historiaRect.h = historiaH;


		SDL_RenderCopy(*renderer, texture.gameintrotex,NULL, &historiaRect);

		go = recebeImput(event,gamestate,state);

		rollup -= 1;
		SDL_Delay(15);

		SDL_RenderPresent(*renderer);
		SDL_RenderClear(*renderer);

		
	}
	

	if(go >= 0)
	{
		go = 0;
	}
	else
	{
		return 0;
	}

	
	opacidade = 0;

	SDL_SetRenderDrawColor(*renderer, 0, 0,0, 255);



	if(gamestate->gamemode == 1)
	{
		while(opacidade < 255 && go == 0)
		{
			
			SDL_SetTextureBlendMode(texture.instructions1tex,SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(texture.instructions1tex,opacidade);
			SDL_RenderCopy(*renderer, texture.instructions1tex,NULL, 0);

			SDL_SetRenderDrawColor(*renderer, 0, 0,0, 255);

			go = recebeImput(event,gamestate,state);	


			opacidade += 1;	
			SDL_RenderPresent(*renderer);
			SDL_RenderClear(*renderer);  
		}

		if(go == 1)
		{
			gamestate->intro = 0;
			return 1;
		}
		else if(go == -1)
		{
			return 0;
		}

		if(go == 0)
		{	
			SDL_Delay(2000);
			opacidade = 255;
		}


		while(opacidade > 0 && go ==0)
		{
			
			
			SDL_SetTextureBlendMode(texture.instructions1tex,SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(texture.instructions1tex,opacidade);
			SDL_RenderCopy(*renderer, texture.instructions1tex,NULL, 0);
			SDL_SetRenderDrawColor(*renderer, 0, 0,0, 255);
			

			go = recebeImput(event,gamestate,state);
			opacidade -= 1;
			SDL_RenderPresent(*renderer);
			SDL_RenderClear(*renderer);  
		}
	}




	if(gamestate->gamemode == 0)
	{
		while(opacidade < 255 && go == 0)
		{
			
			SDL_SetTextureBlendMode(texture.instructionstex,SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(texture.instructionstex,opacidade);
			SDL_RenderCopy(*renderer, texture.instructionstex,NULL, 0);

			SDL_SetRenderDrawColor(*renderer, 0, 0,0, 255);

			go = recebeImput(event,gamestate,state);	


			opacidade += 1;	
			SDL_RenderPresent(*renderer);
			SDL_RenderClear(*renderer);  
		}

		if(go == 1)
		{
			gamestate->intro = 0;
			return 1;
		}
		else if(go == -1)
		{
			return 0;
		}

		if(go == 0)
		{	
			SDL_Delay(2000);
			opacidade = 255;
		}


		while(opacidade > 0 && go ==0)
		{
			
			
			SDL_SetTextureBlendMode(texture.instructionstex,SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(texture.instructionstex,opacidade);
			SDL_RenderCopy(*renderer, texture.instructionstex,NULL, 0);
			SDL_SetRenderDrawColor(*renderer, 0, 0,0, 255);
			

			go = recebeImput(event,gamestate,state);
			opacidade -= 1;
			SDL_RenderPresent(*renderer);
			SDL_RenderClear(*renderer);  
		}
	}

	gamestate->intro = 0;

	if(go == 1)
	{
		gamestate->intro = 0;
		return 1;
	}
	else if(go == -1)
	{
		return 0;
	}

	return 1;

}

void gameended()
{
	SDL_DestroyTexture(texture.backgroundtex );
	
	SDL_DestroyTexture(texture.mousetex);
	SDL_DestroyTexture(texture.bullettex );

	SDL_DestroyTexture(texture.enemytex );
	SDL_DestroyTexture(texture.enemymediumtex );
	SDL_DestroyTexture(texture.enemybosstex );

	SDL_DestroyTexture(texture.portauptex );
	SDL_DestroyTexture(texture.portadowntex);
	SDL_DestroyTexture(texture.portalefttex );
	SDL_DestroyTexture(texture.portarighttex);

	SDL_DestroyTexture(texture.pausetex );

	SDL_DestroyTexture(texture.lifeplustex );
	SDL_DestroyTexture(texture.speedplustex );
	SDL_DestroyTexture(texture.damageplustex);
	SDL_DestroyTexture(texture.arma1tex );
	SDL_DestroyTexture(texture.arma2tex );
	SDL_DestroyTexture(texture.arma3tex );

	SDL_DestroyTexture(texture.playerw1tex );
	SDL_DestroyTexture(texture.playerw2tex );
	SDL_DestroyTexture(texture.playerw3tex );
}