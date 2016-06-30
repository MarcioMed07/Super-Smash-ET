#pragma once

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

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


typedef enum _bulletdirection
{
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	LEFTUP,
	LEFTDOWN,
	RIGHTUP,
	RIGHTDOWN
}DIRECTION;

typedef struct liferegen
{	
	int on;
	int x, y, w, h;
	int amount;
}Lifeplus;

typedef struct morespeed
{
	int on;
	int x, y, w, h;
}Speedplus;

typedef struct moredamage
{
	int on;
	int x, y, w, h;
}Damageplus;

typedef struct armaonfloor1
{
	int on;
	int x, y, w, h;
}Armafloor1;

typedef struct armaonfloor2
{
	int on;
	int x, y, w, h;
}Armafloor2;

typedef struct armaonfloor3
{
	int on;
	int x, y, w, h;
}Armafloor3;

typedef enum _salasnum
{
	SALA1,
	SALA2,
	SALA3,
	SALA4,
	BOSS,
	BONUS
}SALAS;

typedef struct _porta
{
	int x, y, w, h;
}Porta;

typedef struct _wave
{
	int enemyeasytospawn;
	int enemymediumtospawn;
	int enemyhardtospawn;
	int enemybosstospawn;
	int enemyeasy;
	int enemymedium;
	int enemyhard;
	int enemyboss;
	int enemyeasyleft;
	int enemymediumleft;
	int enemyhardleft;
	int enemybossleft;
}Wave;

typedef struct _salasstruct
{
	int x,y,w,h;
	int waveatual;
	int clear; 	
	Wave wave[3];
	Porta portaup;
	Porta portaright;
	Porta portaleft;
	Porta portadown;
}Sala;

typedef struct _player
{
	float x,y;
	float w,h;
	int life;
	char name[20];
	int score;
	int speed;
	int up,down,left,right;
	double angulo;
	int arma;
	int damageplus;
} Player;

typedef struct _parede
{
	int x,y,w,h;
}Parede;

typedef struct _fontes
{
	TTF_Font *scoretela;
	TTF_Font *scorefinal;
}Fontes;

typedef struct _textures
{
	SDL_Texture *backgroundtex;
	SDL_Texture *playerw1tex;
	SDL_Texture	*playerw2tex;
	SDL_Texture	*playerw3tex;
	SDL_Texture *mousetex;
	SDL_Texture *bullettex;
	SDL_Texture *enemytex;
	SDL_Texture *enemybosstex;
	SDL_Texture *enemymediumtex;
	SDL_Texture *portauptex;
	SDL_Texture *portadowntex;
	SDL_Texture *portalefttex;
	SDL_Texture *portarighttex;
	SDL_Texture *pausetex;
	SDL_Texture *lifeplustex;
	SDL_Texture *speedplustex ;
	SDL_Texture *damageplustex ;
	SDL_Texture *arma1tex ;
	SDL_Texture *arma2tex ;
	SDL_Texture *arma3tex ;
	SDL_Texture *scoretela;
	SDL_Texture *scorefinal;

}Texture;

typedef struct _bullet
{
	int on;
	float x;
	float y;
	float xinit;
	float yinit;
	DIRECTION direction;
	int speed;
}Bullet;

typedef struct _enemy
{
	int on;
	float x;
	float y;
	float w;
	float h;
	int life;
	int speed;
	int move;
	int angulo;
}Enemy;

typedef struct _gamestate
{
	int playerup,playerdown,playerleft,playerright;
	Player player;
	Parede parede;
	int ScreenH;
	int ScreenW;
	int mousebuttonl;
	int mousebuttonr;
	float mousex;
	float mousey;
	int rof;
	int rob;
	Sala sala[6];
	SALAS salaatual;
	int pause;
	int musicmute;
	int soundmute;
	int victory;
	int menuroll;
	int intro;
	
}Gamestate;

typedef struct _musics
{
	Mix_Music *musica;
}Musica;

typedef struct _sounds
{
	
}Sounds;

Musica music;

Sounds sound;

Texture texture;

Fontes font;

void loadimages(SDL_Renderer* renderer,Texture *texture);

void desenha(SDL_Renderer* renderer, Gamestate *gamestate,Texture *texture);
