#pragma once
#define MAXBULLETS 1000
#define MAXENEMIES 1000
#define MAXPOWERUP 1000



Bullet bullet[MAXBULLETS];
Bullet enemybullet[MAXBULLETS];
Enemy enemy[MAXENEMIES];
Enemy enemymedium[MAXENEMIES];
Enemy enemyhard[MAXENEMIES];
Enemy enemyboss[MAXENEMIES];

SDL_Rect enemydrawRect[MAXENEMIES][4];
SDL_Rect currentenemyframeRect[MAXENEMIES];

SDL_Rect currentenemymediumframeRect[MAXENEMIES];
SDL_Rect enemymediumdrawRect[MAXENEMIES][ 4 ];

SDL_Rect currentenemybossframeRect[MAXENEMIES];
SDL_Rect enemybossdrawRect[MAXENEMIES][ 4 ];

Lifeplus lifeplus[MAXPOWERUP];
Speedplus speedplus[MAXPOWERUP];
Damageplus damageplus[MAXPOWERUP];
Armafloor1 arma1[MAXPOWERUP];
Armafloor2 arma2[MAXPOWERUP];
Armafloor3 arma3[MAXPOWERUP];

void logica(Gamestate *);

void createbullet(Gamestate* );

void createenemybullet(Gamestate* );

void updatebullet(Gamestate* );

void updateenemybullet(Gamestate *gamestate);

void createenemy(Gamestate* );

void updateenemy(Gamestate* );

void createenemymedium(Gamestate* );

void updateenemymedium(Gamestate* );

/*void createenemyhard(Gamestate* );

void updateenemyhard(Gamestate* );*/

void createboss(Gamestate* );

void updateboss(Gamestate* );

void createlife(int,int);

void updatelife(Gamestate* );

void createspeed(int,int);

void updatespeed(Gamestate* );

void createdamage(int,int);

void updatedamage(Gamestate* );

void createarma1(int,int);

void updatearma1(Gamestate* );

void createarma2(int,int);

void updatearma2(Gamestate* );

void createarma3(int,int);

void updatearma3(Gamestate* );