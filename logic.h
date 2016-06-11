#pragma once
#define MAXBULLETS 1000
#define MAXENEMIES 1000



Bullet bullet[MAXBULLETS];
Enemy enemy[MAXENEMIES];



void logica(Gamestate *);

void createbullet(Gamestate* );

void updatebullet(Gamestate* );

void createenemy(Gamestate* );

void updateenemy(Gamestate* );