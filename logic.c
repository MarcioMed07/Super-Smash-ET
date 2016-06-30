#include <SDL2/SDL.h>
#include "main.h"
#include "logic.h"




int i = 0;

void logica(Gamestate *gamestate)
{
	if(gamestate->sala[gamestate->salaatual].clear == 0)
	{
		if(gamestate->sala[gamestate->salaatual].waveatual >= 0)
		{
			if(gamestate->sala[gamestate->salaatual].wave[gamestate->sala[gamestate->salaatual].waveatual].enemyeasytospawn > 0)
			{				
				if(gamestate->rob == 0)
				{
					createenemy(gamestate);
			   		
					////("criou");
				}				
				
			}

			if(gamestate->sala[gamestate->salaatual].wave[gamestate->sala[gamestate->salaatual].waveatual].enemymediumtospawn > 0)
			{				
				if(gamestate->rob == 0)
				{
					createenemymedium(gamestate);
			   		
					////("criou");
				}				
				
			}

			if(gamestate->sala[gamestate->salaatual].wave[gamestate->sala[gamestate->salaatual].waveatual].enemybosstospawn > 0)
			{				
				if(gamestate->rob == 0)
				{
					createboss(gamestate);
			   		
					////("criou");
				}				
				
			}

			if(	gamestate->sala[gamestate->salaatual].wave[gamestate->sala[gamestate->salaatual].waveatual].enemyeasyleft == 0 &&
				gamestate->sala[gamestate->salaatual].wave[gamestate->sala[gamestate->salaatual].waveatual].enemymediumleft == 0 /*&& 
				gamestate->sala[gamestate->salaatual].wave[gamestate->sala[gamestate->salaatual].waveatual].enemyhardleft == 0*/ &&
				gamestate->sala[gamestate->salaatual].wave[gamestate->sala[gamestate->salaatual].waveatual].enemybossleft == 0 )
			{
				gamestate->sala[gamestate->salaatual].waveatual--;
				gamestate->sala[gamestate->salaatual].wave[gamestate->sala[gamestate->salaatual].waveatual].enemyeasytospawn = gamestate->sala[gamestate->salaatual].wave[gamestate->sala[gamestate->salaatual].waveatual].enemyeasy;
				gamestate->sala[gamestate->salaatual].wave[gamestate->sala[gamestate->salaatual].waveatual].enemymediumtospawn = gamestate->sala[gamestate->salaatual].wave[gamestate->sala[gamestate->salaatual].waveatual].enemymedium;
				gamestate->sala[gamestate->salaatual].wave[gamestate->sala[gamestate->salaatual].waveatual].enemyhardtospawn = gamestate->sala[gamestate->salaatual].wave[gamestate->sala[gamestate->salaatual].waveatual].enemyhard;
				gamestate->sala[gamestate->salaatual].wave[gamestate->sala[gamestate->salaatual].waveatual].enemybosstospawn = gamestate->sala[gamestate->salaatual].wave[gamestate->sala[gamestate->salaatual].waveatual].enemyboss;
			}
				
		}
		else
		{
			gamestate->sala[gamestate->salaatual].clear = 1;
			//gamestate->sala[gamestate->salaatual].waveatual = 0;
		}
	}

	
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
	    						
				
			}
				
		}

	updateenemy(gamestate);
	updateenemymedium(gamestate);
	updateboss(gamestate);
	updatebullet(gamestate);
	updatelife(gamestate);
	updatespeed(gamestate);
	updatedamage(gamestate);
	updatearma1(gamestate);
	updatearma2(gamestate);
	updatearma3(gamestate);

	if(gamestate->player.life > 450)
	{
		gamestate->player.life = 450;
	}

	if(gamestate->player.speed > 8)
	{
		gamestate->player.speed = 8;
	}


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
				

				if(gamestate->player.arma == 1)
				{
					bullet[j].speed = 20;
					gamestate->rof = 20;
				}

				if(gamestate->player.arma == 2)
				{
					bullet[j].speed = 25;
					gamestate->rof = 10;
				}

				if(gamestate->player.arma == 3)
				{
					bullet[j].speed = 15;
					gamestate->rof = 40;
				}

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
			SDL_Rect bulletRect = {bullet[j].x,bullet[j].y,10,10};
			SDL_Rect parederect = {	gamestate->parede.x,gamestate->parede.y,
									gamestate->parede.w,gamestate->parede.h};


			int i;
			for (i = 0; i < MAXENEMIES; i++)
			{
				if(enemy[i].on == 1)
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
				    	
				    	if(gamestate->player.arma == 1)
						{
							enemy[i].life -= (5 + gamestate->player.damageplus) ;
						}

				    	if(gamestate->player.arma == 2)
						{
							enemy[i].life -= (2 + gamestate->player.damageplus);
						}

						if(gamestate->player.arma == 3)
						{
							enemy[i].life -= (15 + gamestate->player.damageplus);
						}


				    }
				}

				if(enemymedium[i].on == 1)
				{
					SDL_Rect enemyRect;

				    enemyRect.x = enemymedium[i].x;
					enemyRect.y = enemymedium[i].y;
					enemyRect.w = enemymedium[i].w;
					enemyRect.h = enemymedium[i].h;
					int Ex = enemyRect.x;
					int EX = enemyRect.x + enemyRect.w;
					int Ey = enemyRect.y;
					int EY = enemyRect.y + enemyRect.h;

				 	if(!((bulletRect.x+bulletRect.w<Ex) || (EX < bulletRect.x) || (bulletRect.y+bulletRect.h < Ey) || (EY < bulletRect.y)))
					{
				    	bullet[j].on = 0;
				    	
				    	if(gamestate->player.arma == 1)
						{
							enemymedium[i].life -= (5 + gamestate->player.damageplus) ;
						}

				    	if(gamestate->player.arma == 2)
						{
							enemymedium[i].life -= (2 + gamestate->player.damageplus) ;
						}

						if(gamestate->player.arma == 3)
						{
							enemymedium[i].life -= (15 + gamestate->player.damageplus);
						}


				    }
				}

			   	if(enemyboss[i].on == 1)
				{
					SDL_Rect enemyRect;
				    enemyRect.x = enemyboss[i].x;
					enemyRect.y = enemyboss[i].y;
					enemyRect.w = enemyboss[i].w;
					enemyRect.h = enemyboss[i].h;
					int Ex = enemyRect.x;
					int EX = enemyRect.x + enemyRect.w;
					int Ey = enemyRect.y;
					int EY = enemyRect.y + enemyRect.h;

				 	if(!((bulletRect.x+bulletRect.w<Ex) || (EX < bulletRect.x) || (bulletRect.y+bulletRect.h < Ey) || (EY < bulletRect.y)))
					{
				    	bullet[j].on = 0;
					    	
				    	if(gamestate->player.arma == 1)
						{
							enemyboss[i].life -= (5 + gamestate->player.damageplus) ;
						}

				    	if(gamestate->player.arma == 2)
						{
							enemyboss[i].life -= (2 + gamestate->player.damageplus) ;
						}

						if(gamestate->player.arma == 3)
						{
							enemyboss[i].life -= (15 + gamestate->player.damageplus);
						}
					}
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

			int position = rand() % 4;
			
			
			
			
			if(position == 0 && gamestate->sala[gamestate->salaatual].portaleft.x != 0)
			{
				enemy[j].x = 100;
			    enemy[j].y = 344;
			    enemy[j].on = 1;
			}
			if(position == 1 && gamestate->sala[gamestate->salaatual].portaright.x != 0)
			{
				enemy[j].x = 1184;
			    enemy[j].y = 344;
			    enemy[j].on = 1;
			}
			if(position == 2 && gamestate->sala[gamestate->salaatual].portaup.x != 0)
			{
				enemy[j].x = 724;
			    enemy[j].y = 100;
			    enemy[j].on = 1;
			}
			if(position == 3 && gamestate->sala[gamestate->salaatual].portadown.x != 0)
			{
				enemy[j].x = 644;
			    enemy[j].y = 768 - 160;
			    enemy[j].on = 1;
			}

			if(enemy[j].on == 1)
			{
				gamestate->sala[gamestate->salaatual].wave[gamestate->sala[gamestate->salaatual].waveatual].enemyeasytospawn--;
				enemy[j].w = 60;
				enemy[j].h = 103;
				enemy[j].life = 30;
				enemy[j].speed = 2;
				enemy[j].move = 1;
				gamestate->rob = 30;
			}

			break;
		}	
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


			while(enemy[i].move == 1)
			{
				if (gamestate->player.x > enemy[i].x && !(gamestate->player.y > enemy[i].y) && !(gamestate->player.y < enemy[i].y))
				{
					enemy[i].x += enemy[i].speed;
					enemy[i].angulo = 90;
					//enemy[i].move = 0;
					break;
				}
			    
			    if(gamestate->player.x < enemy[i].x && !(gamestate->player.y > enemy[i].y) && !(gamestate->player.y < enemy[i].y))
			    {
			    	enemy[i].x -= enemy[i].speed;
			    	enemy[i].angulo = 270;
			    	//enemy[i].move = 0;
			    	break;
			    }
			    
			    if (gamestate->player.y > enemy[i].y && !(gamestate->player.x < enemy[i].x) && !(gamestate->player.x > enemy[i].x))
			    {
					enemy[i].y += enemy[i].speed;
					enemy[i].angulo = 180;
					//enemy[i].move = 0;
					break;
			    }
			    if (gamestate->player.y < enemy[i].y && !(gamestate->player.x < enemy[i].x) && !(gamestate->player.x > enemy[i].x))
			    {
			    	enemy[i].y -= enemy[i].speed;
			    	enemy[i].angulo = 360;
			    	//enemy[i].move = 0;
			    	break;
			    }
			    if(gamestate->player.x > enemy[i].x && gamestate->player.y > enemy[i].y)
			    {
			    	enemy[i].x += enemy[i].speed ;
			    	enemy[i].y += enemy[i].speed ;
			    	enemy[i].angulo = 135;
			    	//enemy[i].move = 0;
			    	break;
			    }
			    if(gamestate->player.x > enemy[i].x && gamestate->player.y < enemy[i].y)
			    {
			    	enemy[i].x += enemy[i].speed ;
			    	enemy[i].y -= enemy[i].speed ;
			    	enemy[i].angulo = 45;
			    	//enemy[i].move = 0;
			    	break;
			    }
			    if(gamestate->player.x < enemy[i].x && gamestate->player.y > enemy[i].y)
			    {
			    	enemy[i].x -= enemy[i].speed ;
			    	enemy[i].y += enemy[i].speed ;
			    	enemy[i].angulo = 225;
			    	//enemy[i].move = 0;
			    	break;
			    }
			    if(gamestate->player.x < enemy[i].x && gamestate->player.y < enemy[i].y)
			    {
			    	enemy[i].x -= enemy[i].speed ;
			    	enemy[i].y -= enemy[i].speed ;
			    	enemy[i].angulo = 315;
			    	//enemy[i].move = 0;
			    	break;
			    }
			    
			}

			if(enemy[i].life <= 0)
			{
				int drop = rand() % 100;
				
				gamestate->player.score += 10;

				if(drop >= 0 && drop < 5)
				{
					createspeed(enemy[i].x, enemy[i].y);
				}
				if(drop >= 5 && drop < 10)
				{
					createdamage(enemy[i].x, enemy[i].y);
				}
				if(drop >= 10 && drop < 15)
				{
					createarma3(enemy[i].x, enemy[i].y);
				}
				if(drop >= 15 && drop < 20)
				{
					createarma1(enemy[i].x, enemy[i].y);
				}
				if(drop >= 20 && drop < 30)
				{
					createlife(enemy[i].x, enemy[i].y);
				}
				if(drop >= 30)
				{
					gamestate->player.score += 10;					
				}
				enemy[i].on = 0;
				// enemy[i].w = 0;
				// enemy[i].h = 0;
				// enemy[i].x = 0;
				// enemy[i].y = 0;
				enemy[i].life = 0;
				enemy[i].speed = 0;
				enemy[i].move = 0;
				gamestate->sala[gamestate->salaatual].wave[gamestate->sala[gamestate->salaatual].waveatual].enemyeasyleft--;
			}

		
		}		
		
	}

}

void createenemymedium(Gamestate *gamestate)
{

	int j;

	
	for (j = 0; j < MAXENEMIES; j++)
	{

		
		if(enemymedium[j].on == 0)
		{	

			int position = rand() % 4;		
			
			
			
			if(position == 0 && gamestate->sala[gamestate->salaatual].portaleft.x != 0)
			{
				enemymedium[j].x = 100;
			    enemymedium[j].y = 344;
			    enemymedium[j].on = 1;
			}
			if(position == 1 && gamestate->sala[gamestate->salaatual].portaright.x != 0)
			{
				enemymedium[j].x = 1184;
			    enemymedium[j].y = 344;
			    enemymedium[j].on = 1;
			}
			if(position == 2 && gamestate->sala[gamestate->salaatual].portaup.x != 0)
			{
				enemymedium[j].x = 724;
			    enemymedium[j].y = 100;
			    enemymedium[j].on = 1;
			}
			if(position == 3 && gamestate->sala[gamestate->salaatual].portadown.x != 0)
			{
				enemymedium[j].x = 644;
			    enemymedium[j].y = 768 - 160;
			    enemymedium[j].on = 1;
			}

			if(enemymedium[j].on == 1)
			{
				gamestate->sala[gamestate->salaatual].wave[gamestate->sala[gamestate->salaatual].waveatual].enemymediumtospawn--;
				enemymedium[j].w = 60;
				enemymedium[j].h = 86;
				enemymedium[j].life = 60;
				enemymedium[j].speed = 1;
				enemymedium[j].move = 1;
				gamestate->rob = 30;
			}

			break;
		}	
	}
}

void updateenemymedium(Gamestate *gamestate)
{

	int i;
	for (i = 0; i < MAXENEMIES; i++)
	{
		if(enemymedium[i].on == 1)
		{
			SDL_Rect playerRect = {	gamestate->player.x,gamestate->player.y,
							gamestate->player.w,gamestate->player.h};
			SDL_Rect enemyRect;

			enemyRect.x = enemymedium[i].x;
			enemyRect.y = enemymedium[i].y;
			enemyRect.w = enemymedium[i].w;
			enemyRect.h = enemymedium[i].h;

			
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
				enemymedium[i].move = 0;
				gamestate->player.life = gamestate->player.life - 2;
			}
			else
			{
				enemymedium[i].move = 1;
			}


			while(enemymedium[i].move == 1)
			{
				if (gamestate->player.x > enemymedium[i].x && !(gamestate->player.y > enemymedium[i].y) && !(gamestate->player.y < enemymedium[i].y))
				{
					enemymedium[i].x += enemymedium[i].speed;
					enemymedium[i].angulo = 90;
					//enemy[i].move = 0;
					break;
				}
			    
			    if(gamestate->player.x < enemymedium[i].x && !(gamestate->player.y > enemymedium[i].y) && !(gamestate->player.y < enemymedium[i].y))
			    {
			    	enemymedium[i].x -= enemymedium[i].speed;
			    	enemymedium[i].angulo = 270;
			    	//enemy[i].move = 0;
			    	break;
			    }
			    
			    if (gamestate->player.y > enemymedium[i].y && !(gamestate->player.x < enemymedium[i].x) && !(gamestate->player.x > enemymedium[i].x))
			    {
					enemymedium[i].y += enemymedium[i].speed;
					enemymedium[i].angulo = 180;
					//enemy[i].move = 0;
					break;
			    }
			    if (gamestate->player.y < enemymedium[i].y && !(gamestate->player.x < enemymedium[i].x) && !(gamestate->player.x > enemymedium[i].x))
			    {
			    	enemymedium[i].y -= enemymedium[i].speed;
			    	enemymedium[i].angulo = 360;
			    	//enemy[i].move = 0;
			    	break;
			    }
			    if(gamestate->player.x > enemymedium[i].x && gamestate->player.y > enemymedium[i].y)
			    {
			    	enemymedium[i].x += enemymedium[i].speed ;
			    	enemymedium[i].y += enemymedium[i].speed ;
			    	enemymedium[i].angulo = 135;
			    	//enemy[i].move = 0;
			    	break;
			    }
			    if(gamestate->player.x > enemymedium[i].x && gamestate->player.y < enemymedium[i].y)
			    {
			    	enemymedium[i].x += enemymedium[i].speed ;
			    	enemymedium[i].y -= enemymedium[i].speed ;
			    	enemymedium[i].angulo = 45;
			    	//enemy[i].move = 0;
			    	break;
			    }
			    if(gamestate->player.x < enemymedium[i].x && gamestate->player.y > enemymedium[i].y)
			    {
			    	enemymedium[i].x -= enemymedium[i].speed ;
			    	enemymedium[i].y += enemymedium[i].speed ;
			    	enemymedium[i].angulo = 225;
			    	//enemy[i].move = 0;
			    	break;
			    }
			    if(gamestate->player.x < enemymedium[i].x && gamestate->player.y < enemymedium[i].y)
			    {
			    	enemymedium[i].x -= enemymedium[i].speed ;
			    	enemymedium[i].y -= enemymedium[i].speed ;
			    	enemymedium[i].angulo = 315;
			    	//enemy[i].move = 0;
			    	break;
			    }
			    
			}

			if(enemymedium[i].life <= 0)
			{	
				int drop = rand() % 100;

				gamestate->player.score += 30;
				if(drop >= 0 && drop < 10)
				{
					createspeed(enemymedium[i].x, enemymedium[i].y);
				}
				if(drop >= 10 && drop < 20)
				{
					createdamage(enemymedium[i].x, enemymedium[i].y);
				}
				if(drop >= 20 && drop < 30)
				{
					createarma3(enemymedium[i].x, enemymedium[i].y);
				}
				if(drop >= 30 && drop < 35)
				{
					createarma2(enemymedium[i].x, enemymedium[i].y);
				}
				if(drop >= 35 && drop < 50)
				{
					createlife(enemymedium[i].x, enemymedium[i].y);
				}
				if(drop >= 50)
				{
					gamestate->player.score += 10;
				}
				enemymedium[i].on = 0;
				// enemymedium[i].w = 0;
				// enemymedium[i].h = 0;
				// enemymedium[i].x = 0;
				// enemymedium[i].y = 0;
				enemymedium[i].life = 0;
				enemymedium[i].speed = 0;
				enemymedium[i].move = 0;
				gamestate->sala[gamestate->salaatual].wave[gamestate->sala[gamestate->salaatual].waveatual].enemymediumleft--;
			}

		
		}		
		
	}

}




void createboss(Gamestate *gamestate)
{

	int j;

	
	for (j = 0; j < MAXENEMIES; j++)
	{
		
		if(enemyboss[j].on == 0)
		{			
			    enemyboss[j].on = 1;						

			if(enemyboss[j].on == 1)
			{
				gamestate->sala[gamestate->salaatual].wave[gamestate->sala[gamestate->salaatual].waveatual].enemybosstospawn--;
				enemyboss[j].x = 1184;
			    enemyboss[j].y = 340;
				enemyboss[j].w = 60 * 2;
				enemyboss[j].h = 86 * 2;
				enemyboss[j].life = 900;
				enemyboss[j].speed = 4;
				enemyboss[j].move = 1;
				gamestate->rob = 30;
				break;
			}

			
		}	
	}
}

void updateboss(Gamestate *gamestate)
{

	int i;
	for (i = 0; i < MAXENEMIES; i++)
	{
		if(enemyboss[i].on == 1)
		{
			SDL_Rect playerRect = {	gamestate->player.x,gamestate->player.y,
							gamestate->player.w,gamestate->player.h};
			SDL_Rect enemyRect;

			enemyRect.x = enemyboss[i].x;
			enemyRect.y = enemyboss[i].y;
			enemyRect.w = enemyboss[i].w;
			enemyRect.h = enemyboss[i].h;

			
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
				enemyboss[i].move = 0;
				gamestate->player.life = gamestate->player.life - 5;
			}
			else
			{
				enemyboss[i].move = 1;
			}


			while(enemyboss[i].move == 1)
			{
				if (gamestate->player.x > enemyboss[i].x && !(gamestate->player.y > enemyboss[i].y) && !(gamestate->player.y < enemyboss[i].y))
				{
					enemyboss[i].x += enemyboss[i].speed;
					enemyboss[i].angulo = 90;
					//enemy[i].move = 0;
					break;
				}
			    
			    if(gamestate->player.x < enemyboss[i].x && !(gamestate->player.y > enemyboss[i].y) && !(gamestate->player.y < enemyboss[i].y))
			    {
			    	enemyboss[i].x -= enemyboss[i].speed;
			    	enemyboss[i].angulo = 270;
			    	//enemy[i].move = 0;
			    	break;
			    }
			    
			    if (gamestate->player.y > enemyboss[i].y && !(gamestate->player.x < enemyboss[i].x) && !(gamestate->player.x > enemyboss[i].x))
			    {
					enemyboss[i].y += enemyboss[i].speed;
					enemyboss[i].angulo = 180;
					//enemy[i].move = 0;
					break;
			    }
			    if (gamestate->player.y < enemyboss[i].y && !(gamestate->player.x < enemyboss[i].x) && !(gamestate->player.x > enemyboss[i].x))
			    {
			    	enemyboss[i].y -= enemyboss[i].speed;
			    	enemyboss[i].angulo = 360;
			    	//enemy[i].move = 0;
			    	break;
			    }
			    if(gamestate->player.x > enemyboss[i].x && gamestate->player.y > enemyboss[i].y)
			    {
			    	enemyboss[i].x += enemyboss[i].speed ;
			    	enemyboss[i].y += enemyboss[i].speed ;
			    	enemyboss[i].angulo = 135;
			    	//enemy[i].move = 0;
			    	break;
			    }
			    if(gamestate->player.x > enemyboss[i].x && gamestate->player.y < enemyboss[i].y)
			    {
			    	enemyboss[i].x += enemyboss[i].speed ;
			    	enemyboss[i].y -= enemyboss[i].speed ;
			    	enemyboss[i].angulo = 45;
			    	//enemy[i].move = 0;
			    	break;
			    }
			    if(gamestate->player.x < enemyboss[i].x && gamestate->player.y > enemyboss[i].y)
			    {
			    	enemyboss[i].x -= enemyboss[i].speed ;
			    	enemyboss[i].y += enemyboss[i].speed ;
			    	enemyboss[i].angulo = 225;
			    	//enemy[i].move = 0;
			    	break;
			    }
			    if(gamestate->player.x < enemyboss[i].x && gamestate->player.y < enemyboss[i].y)
			    {
			    	enemyboss[i].x -= enemyboss[i].speed ;
			    	enemyboss[i].y -= enemyboss[i].speed ;
			    	enemyboss[i].angulo = 315;
			    	//enemy[i].move = 0;
			    	break;
			    }
			    
			}

			if(enemyboss[i].life <= 0)
			{	
				gamestate->player.score += 500;
				enemyboss[i].on = 0;
				// enemymedium[i].w = 0;
				// enemymedium[i].h = 0;
				// enemymedium[i].x = 0;
				// enemymedium[i].y = 0;
				enemyboss[i].life = 0;
				enemyboss[i].speed = 0;
				enemyboss[i].move = 0;
				gamestate->victory = 1;
			}

		
		}		
		
	}

}

void createlife(int x,int y)
{
	int j = 0;

	
	for (j = 0; j < MAXPOWERUP; j++)
	{
		


		if(lifeplus[j].on == 0)
		{				
			lifeplus[j].on = 1;	
			if(lifeplus[j].on == 1)
			{
				lifeplus[j].amount = 10 + (rand() % 10);
				lifeplus[j].x = x;
				lifeplus[j].y = y;
				lifeplus[j].w = 20;
				lifeplus[j].h = 20;
				break;
			}		
		}
		
		
	}
}

void createspeed(int x,int y)
{
	int j = 0;
	
	for (j = 0; j < MAXPOWERUP; j++)
	{
		

		if(speedplus[j].on == 0)
		{	
			speedplus[j].on = 1;
			if(speedplus[j].on == 1)
			{
				speedplus[j].x = x;
				speedplus[j].y = y;
				speedplus[j].w = 20;
				speedplus[j].h = 20;
				break;
			}
		}
	}
}

void createdamage(int x,int y)
{
	int j = 0;
	
	for (j = 0; j < MAXPOWERUP; j++)
	{
		//("damage");

		if(damageplus[j].on == 0)
		{	
			damageplus[j].on = 1;
			if(damageplus[j].on == 1)
			{
				damageplus[j].x = x;
				damageplus[j].y = y;
				damageplus[j].w = 20;
				damageplus[j].h = 20;
				break;
			}
		}
	}
}

void createarma1(int x,int y)
{
	int j = 0;
	
	for (j = 0; j < MAXPOWERUP; j++)
	{
		//("arma1");

		if(arma1[j].on == 0)
		{	
			arma1[j].on = 1;
			if(arma1[j].on == 1)
			{
				arma1[j].x = x;
				arma1[j].y = y;
				arma1[j].w = 20;
				arma1[j].h = 20;
				break;
			}
		}
	}
}

void createarma2(int x,int y)
{
	int j = 0;
	
	for (j = 0; j < MAXPOWERUP; j++)
	{
		//("arma2");

		if(arma2[j].on == 0)
		{	
			arma2[j].on = 1;
			if(arma2[j].on == 1)
			{				
				arma2[j].x = x;
				arma2[j].y = y;
				arma2[j].w = 20;
				arma2[j].h = 20;
				break;
			}
		}
	}
}

void createarma3(int x,int y)
{
	int j = 0;
	
	for (j = 0; j < MAXPOWERUP; j++)
	{
		//("arma3");

		if(arma3[j].on == 0)
		{	
			arma3[j].on = 1;
			if(arma3[j].on == 1)
			{
				arma3[j].x = x;
				arma3[j].y = y;
				arma3[j].w = 20;
				arma3[j].h = 20;
				break;
			}
		}
	}
}

void updatelife(Gamestate *gamestate)
{

	int i;
	for (i = 0; i < MAXPOWERUP; i++)
	{
		if(lifeplus[i].on == 1)
		{
			SDL_Rect playerRect = {	gamestate->player.x,gamestate->player.y,
							gamestate->player.w,gamestate->player.h};
			SDL_Rect lifeRect;

			lifeRect.x = lifeplus[i].x;
			lifeRect.y = lifeplus[i].y;
			lifeRect.w = lifeplus[i].w;
			lifeRect.h = lifeplus[i].h;

			
			int Px = playerRect.x;
			int PX = playerRect.x + playerRect.w;
			int Py = playerRect.y;
			int PY = playerRect.y + playerRect.h;

			int Ex = lifeRect.x;
			int EX = lifeRect.x + lifeRect.w;
			int Ey = lifeRect.y;
			int EY = lifeRect.y + lifeRect.h;

			if(!((PX<Ex) || (EX<Px) || (PY < Ey) || (EY < Py)) && lifeplus[i].on == 1)
			{
				lifeplus[i].on = 0;
				

				gamestate->player.life = gamestate->player.life + lifeplus[i].amount;

				
				
			}
		}
	}
}

void updatespeed(Gamestate *gamestate)
{

	int i;
	for (i = 0; i < MAXPOWERUP; i++)
	{
		if(speedplus[i].on == 1)
		{
			SDL_Rect playerRect = {	gamestate->player.x,gamestate->player.y,
							gamestate->player.w,gamestate->player.h};
			SDL_Rect speedRect;

			speedRect.x = speedplus[i].x;
			speedRect.y = speedplus[i].y;
			speedRect.w = speedplus[i].w;
			speedRect.h = speedplus[i].h;

			
			int Px = playerRect.x;
			int PX = playerRect.x + playerRect.w;
			int Py = playerRect.y;
			int PY = playerRect.y + playerRect.h;

			int Ex = speedRect.x;
			int EX = speedRect.x + speedRect.w;
			int Ey = speedRect.y;
			int EY = speedRect.y + speedRect.h;

			if(!((PX<Ex) || (EX<Px) || (PY < Ey) || (EY < Py)) && speedplus[i].on == 1)
			{
				speedplus[i].on = 0;

				gamestate->player.speed = gamestate->player.speed + 2;
				
			}
		}
	}
}

void updatedamage(Gamestate *gamestate)
{

	int i;
	for (i = 0; i < MAXPOWERUP; i++)
	{
		if(damageplus[i].on == 1)
		{
			SDL_Rect playerRect = {	gamestate->player.x,gamestate->player.y,
							gamestate->player.w,gamestate->player.h};
			SDL_Rect damageRect;

			damageRect.x = damageplus[i].x;
			damageRect.y = damageplus[i].y;
			damageRect.w = damageplus[i].w;
			damageRect.h = damageplus[i].h;

			
			int Px = playerRect.x;
			int PX = playerRect.x + playerRect.w;
			int Py = playerRect.y;
			int PY = playerRect.y + playerRect.h;

			int Ex = damageRect.x;
			int EX = damageRect.x + damageRect.w;
			int Ey = damageRect.y;
			int EY = damageRect.y + damageRect.h;

			if(!((PX<Ex) || (EX<Px) || (PY < Ey) || (EY < Py)) && damageplus[i].on == 1)
			{
				damageplus[i].on = 0;

				gamestate->player.damageplus = gamestate->player.damageplus + 1;
				
			}
		}
	}
}

void updatearma1(Gamestate *gamestate)
{

	int i;
	for (i = 0; i < MAXPOWERUP; i++)
	{
		if(arma1[i].on == 1)
		{
			SDL_Rect playerRect = {	gamestate->player.x,gamestate->player.y,
							gamestate->player.w,gamestate->player.h};
			SDL_Rect arma1Rect;

			arma1Rect.x = arma1[i].x;
			arma1Rect.y = arma1[i].y;
			arma1Rect.w = arma1[i].w;
			arma1Rect.h = arma1[i].h;

			
			int Px = playerRect.x;
			int PX = playerRect.x + playerRect.w;
			int Py = playerRect.y;
			int PY = playerRect.y + playerRect.h;

			int Ex = arma1Rect.x;
			int EX = arma1Rect.x + arma1Rect.w;
			int Ey = arma1Rect.y;
			int EY = arma1Rect.y + arma1Rect.h;

			if(!((PX<Ex) || (EX<Px) || (PY < Ey) || (EY < Py)) && arma1[i].on == 1)
			{
				arma1[i].on = 0;

				gamestate->player.arma = 1;
				
			}
		}
	}
}

void updatearma2(Gamestate *gamestate)
{

	int i;
	for (i = 0; i < MAXPOWERUP; i++)
	{
		if(arma2[i].on == 1)
		{
			SDL_Rect playerRect = {	gamestate->player.x,gamestate->player.y,
							gamestate->player.w,gamestate->player.h};
			SDL_Rect arma2Rect;

			arma2Rect.x = arma2[i].x;
			arma2Rect.y = arma2[i].y;
			arma2Rect.w = arma2[i].w;
			arma2Rect.h = arma2[i].h;

			
			int Px = playerRect.x;
			int PX = playerRect.x + playerRect.w;
			int Py = playerRect.y;
			int PY = playerRect.y + playerRect.h;

			int Ex = arma2Rect.x;
			int EX = arma2Rect.x + arma2Rect.w;
			int Ey = arma2Rect.y;
			int EY = arma2Rect.y + arma2Rect.h;

			if(!((PX<Ex) || (EX<Px) || (PY < Ey) || (EY < Py)) && arma2[i].on == 1)
			{
				arma2[i].on = 0;

				gamestate->player.arma = 2;
				
			}
		}
	}
}

void updatearma3(Gamestate *gamestate)
{

	int i;
	for (i = 0; i < MAXPOWERUP; i++)
	{
		if(arma3[i].on == 1)
		{
			SDL_Rect playerRect = {	gamestate->player.x,gamestate->player.y,
							gamestate->player.w,gamestate->player.h};
			SDL_Rect arma3Rect;

			arma3Rect.x = arma3[i].x;
			arma3Rect.y = arma3[i].y;
			arma3Rect.w = arma3[i].w;
			arma3Rect.h = arma3[i].h;

			
			int Px = playerRect.x;
			int PX = playerRect.x + playerRect.w;
			int Py = playerRect.y;
			int PY = playerRect.y + playerRect.h;

			int Ex = arma3Rect.x;
			int EX = arma3Rect.x + arma3Rect.w;
			int Ey = arma3Rect.y;
			int EY = arma3Rect.y + arma3Rect.h;

			if(!((PX<Ex) || (EX<Px) || (PY < Ey) || (EY < Py)) && arma3[i].on == 1)
			{
				arma3[i].on = 0;

				gamestate->player.arma = 3;
				
			}
		}
	}
}