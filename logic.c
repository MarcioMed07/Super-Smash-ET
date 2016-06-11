#include <SDL2/SDL.h>
#include "main.h"
#include "logic.h"




int i = 0;

void logica(Gamestate *gamestate)
{
	createenemy(gamestate);
	
	SDL_Rect playerRect = {	gamestate->player.x,gamestate->player.y,
							gamestate->player.w,gamestate->player.h};
	SDL_Rect parederect = {	gamestate->parede.x,gamestate->parede.y,
							gamestate->parede.w,gamestate->parede.h};
	

	if 	(!(playerRect.y < parederect.y))
		if(gamestate->playerup == 1)
		{
			gamestate->player.y -= gamestate->player.speed;	
		}


	if (!(playerRect.y+playerRect.h > parederect.y+parederect.h))
		if(gamestate->playerdown == 1)
		{
			gamestate->player.y += gamestate->player.speed;			
		}
	
	if (!(playerRect.x < parederect.x))
		if(gamestate->playerleft == 1)
		{
			gamestate->player.x -= gamestate->player.speed;			
		}

		
	if(!(playerRect.x+playerRect.w > parederect.x+parederect.w))
		if(gamestate->playerright == 1)
		{
			gamestate->player.x += gamestate->player.speed;
		}

	if( gamestate->player.down == 1 || gamestate->player.up == 1 || gamestate->player.left == 1 || gamestate->player.right == 1)
		{
			if(gamestate->rof == 0)
			{
				
	    		createbullet(gamestate);
	    						
				gamestate->rof = 15;
			}
				
		}
/*
		switch(gamestate->sala.salaatual)
		{
			case SALA1:
				gamestate->sala.x = 0;
			    gamestate->sala.y = 0;
			    gamestate->sala.w = 1366;
			    gamestate->sala.h = 768;
			    gamestate->sala.enemytype1 = 8;
			    gamestate->sala.enemytype2 = 0;
			    gamestate->sala.enemytype3 = 0;
			    gamestate->sala.wave = 3;

			    break;
			case SALA2:
				gamestate->sala.x = 0;
			    gamestate->sala.y = 768;
			    gamestate->sala.w = 1366;
			    gamestate->sala.h = 768;
			    break;
			case SALA3:
				gamestate->sala.x = 1366;
			    gamestate->sala.y = 0;
			    gamestate->sala.w = 1366;
			    gamestate->sala.h = 768;
			    break;
			case SALA4:
				gamestate->sala.x = 1366;
			    gamestate->sala.y = 768;
			    gamestate->sala.w = 1366;
			    gamestate->sala.h = 768;
			    break;
			case BOSS:
				gamestate->sala.x = 1366*2;
			    gamestate->sala.y = 0;
			    gamestate->sala.w = 1366;
			    gamestate->sala.h = 768;
			    break;
			case BONUS:
				gamestate->sala.x = 1366*2;
			    gamestate->sala.y = 768;
			    gamestate->sala.w = 1366;
			    gamestate->sala.h = 768;
			    break;
		}
*/
	
	updateenemy(gamestate);
	updatebullet(gamestate);

	if(gamestate->rof > 0)
		gamestate->rof --;

	if(gamestate->rob > 0)
		gamestate->rob --;
	
   
}

void createbullet(Gamestate *gamestate)
{

	int j;
	
	for (j = 0; j < MAXBULLETS; j++)
	{
		
			if(bullet[j].on == 0)
			{	

				bullet[j].on = 1;
				

				if( gamestate->player.down == 1)
				{
					bullet[j].xinit = gamestate->player.x + (gamestate->player.w/2);
					bullet[j].yinit = gamestate->player.y + gamestate->player.h;
					bullet[j].direction = DOWN;				
				}
				if ( gamestate->player.up == 1 )
				{
					bullet[j].xinit = gamestate->player.x + (gamestate->player.w/2) ;
					bullet[j].yinit = gamestate->player.y;
					bullet[j].direction = UP;
				}
				if (gamestate->player.left == 1)
				{
					bullet[j].xinit = gamestate->player.x;
					bullet[j].yinit = gamestate->player.y + (gamestate->player.h/2) ;
					bullet[j].direction = LEFT;				
				}
				if (gamestate->player.right == 1)
				{
					bullet[j].xinit = gamestate->player.x + gamestate->player.w;
					bullet[j].yinit = gamestate->player.y + (gamestate->player.h/2) ;
					bullet[j].direction = RIGHT;
				}
				if (gamestate->player.right == 1 && gamestate->player.up == 1)
				{
					bullet[j].xinit = gamestate->player.x + gamestate->player.w;
					bullet[j].yinit = gamestate->player.y ;
					bullet[j].direction = RIGHTUP;
				}
				if (gamestate->player.right == 1 && gamestate->player.down == 1)
				{
					bullet[j].xinit = gamestate->player.x + gamestate->player.w;
					bullet[j].yinit = gamestate->player.y + gamestate->player.h ;
					bullet[j].direction = RIGHTDOWN;
				}
				if (gamestate->player.left == 1 && gamestate->player.up == 1)
				{
					bullet[j].xinit = gamestate->player.x;
					bullet[j].yinit = gamestate->player.y;
					bullet[j].direction = LEFTUP;
				}
				if (gamestate->player.left == 1 && gamestate->player.down == 1)
	    		{
	    			bullet[j].xinit = gamestate->player.x;
					bullet[j].yinit = gamestate->player.y + gamestate->player.h ;
	    			bullet[j].direction = LEFTDOWN;	 
	    		}
	    		bullet[j].x = bullet[j].xinit;
				bullet[j].y = bullet[j].yinit;
				bullet[j].speed = 30;

				return;
			}			
	}
}

void updatebullet(Gamestate *gamestate)
{

	int j;
	for (j = 0; j < MAXBULLETS; j++)
	{
		if(bullet[j].on == 1)
		{
			SDL_Rect bulletRect = {bullet[j].x,bullet[j].y,5,5};
			SDL_Rect parederect = {	gamestate->parede.x,gamestate->parede.y,
									gamestate->parede.w,gamestate->parede.h};


			int i;
			for (i = 0; i < MAXENEMIES; i++)
			{
				SDL_Rect enemyRect;

				enemyRect.x = enemy[i].x;
				enemyRect.y = enemy[i].y;
				enemyRect.w = enemy[i].w;
				enemyRect.h = enemy[i].h;
				int Ex = enemyRect.x;
				int EX = enemyRect.x + enemyRect.w;
				int Ey = enemyRect.y;
				int EY = enemyRect.y + enemyRect.h;

			 	if(!((bulletRect.x+bulletRect.w<Ex) || (EX < bulletRect.x) || (bulletRect.y+bulletRect.h < Ey) || (EY < bulletRect.y)))
				{
			    	bullet[j].on = 0;
			    	enemy[i].life -- ;

			    }
			}

			if 	((bulletRect.y <= 100) ||
				 (bulletRect.y+bulletRect.h >= 668)||
				 (bulletRect.x <= 100)||
				 (bulletRect.x+bulletRect.w >= 1266))
			{
				bullet[j].on = 0;
				
			}
			else
			{
				if( bullet[j].direction == DOWN)
				{
					bullet[j].y += bullet[j].speed;				
				}
				if ( bullet[j].direction == UP )
				{
					bullet[j].y -= bullet[j].speed;	
				}
				if (bullet[j].direction == LEFT)
				{
					bullet[j].x -= bullet[j].speed;	
				}
				if (bullet[j].direction == RIGHT)
				{
					bullet[j].x += bullet[j].speed;bullet[j].speed;
				}
				if (bullet[j].direction == RIGHTUP)
				{
					bullet[j].y -= bullet[j].speed/2;	
					bullet[j].x += bullet[j].speed/2;
				}
				if (bullet[j].direction == RIGHTDOWN)
				{
					bullet[j].y += bullet[j].speed/2;	
					bullet[j].x += bullet[j].speed/2;
				}
				if (bullet[j].direction == LEFTUP)
				{
					bullet[j].y -= bullet[j].speed/2;	
					bullet[j].x -= bullet[j].speed/2;
				}
				if (bullet[j].direction == LEFTDOWN)
	    		{
	    			bullet[j].y += bullet[j].speed/2;	
					bullet[j].x -= bullet[j].speed/2;
	    		}
	    	}

			
		}
		else
		{
			bullet[j].on = 0;
			bullet[j].x = 0;
			bullet[j].y = 0;
			bullet[j].xinit = 0;
			bullet[j].yinit = 0;
			bullet[j].direction = NONE;
			bullet[j].speed = 0;
		}
		
	}
}

void createenemy(Gamestate *gamestate)
{

	int j;
	
	for (j = 0; j < MAXENEMIES; j++)
	{
		
		if(enemy[j].on == 0)
		{	
			enemy[j].on = 1;
			enemy[j].w = 80;
			enemy[j].h = 50;
			enemy[j].x = 1266;
			enemy[j].y = (768/2)-(enemy[j].h/2);
			enemy[j].life = 30;
			enemy[j].speed = 3;
			enemy[j].move = 1;
		}
		return;
			
	}
}

void updateenemy(Gamestate *gamestate)
{

	int i;
	for (i = 0; i < MAXENEMIES; i++)
	{
		if(enemy[i].on == 1)
		{
			SDL_Rect playerRect = {	gamestate->player.x,gamestate->player.y,
							gamestate->player.w,gamestate->player.h};
			SDL_Rect enemyRect;

			enemyRect.x = enemy[i].x;
			enemyRect.y = enemy[i].y;
			enemyRect.w = enemy[i].w;
			enemyRect.h = enemy[i].h;

			
			int Px = playerRect.x;
			int PX = playerRect.x + playerRect.w;
			int Py = playerRect.y;
			int PY = playerRect.y + playerRect.h;

			int Ex = enemyRect.x;
			int EX = enemyRect.x + enemyRect.w;
			int Ey = enemyRect.y;
			int EY = enemyRect.y + enemyRect.h;

			if(!((PX<Ex) || (EX<Px) || (PY < Ey) || (EY < Py)))
			{
				enemy[i].move = 0;
				gamestate->player.life = gamestate->player.life - 1;
			}
			else
			{
				enemy[i].move = 1;
			}


			if(enemy[i].move == 1)
			{
				if (gamestate->player.x > enemy[i].x)
					enemy[i].x += enemy[i].speed;
			    else if(gamestate->player.x < enemy[i].x)
			    	enemy[i].x -= enemy[i].speed;
			    else;

			    if (gamestate->player.y > enemy[i].y)
					enemy[i].y += enemy[i].speed;
			    else  if (gamestate->player.y < enemy[i].y)
			    	enemy[i].y -= enemy[i].speed;
			    else;
			}

			if(enemy[i].life <= 0)
			{
				enemy[i].on = 0;
				enemy[i].w = 0;
				enemy[i].h = 0;
				enemy[i].x = 0;
				enemy[i].y = 0;
				enemy[i].life = 0;
				enemy[i].speed = 0;
				enemy[i].move = 0;
			}

		
		}		
		
	}

}