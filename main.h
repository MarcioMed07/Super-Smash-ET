#pragma once

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>
#include <string.h>


#define MAX_ARRAY 10
#define MAX_NOME 50





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
	char name[200];
	int score;
	int speed;
	int up,down,left,right;
	double angulo;
	int arma;
	int damageplus;
	int frame;
	int bombbar;
	int bombpressed;
	int defeat;
	int framedead;
	int cont;
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
	SDL_Texture *playerw1hurttex;
	SDL_Texture	*playerw2hurttex;
	SDL_Texture	*playerw3hurttex;
	SDL_Texture *playerw1deadtex;
	SDL_Texture *playerw2deadtex;
	SDL_Texture *playerw3deadtex;
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
	SDL_Texture *losetex;
	SDL_Texture *gameintrotex;
	SDL_Texture *wintex;
	SDL_Texture *instructionstex;
	SDL_Texture *instructions1tex;
	SDL_Texture *openingtex;
	SDL_Texture *logotex;
	SDL_Texture *options0tex;
	SDL_Texture *options1tex;
	SDL_Texture *menutex;
	SDL_Texture *menurolltex;
	SDL_Texture *creditstex;
	SDL_Texture *highscorestex;
	SDL_Texture *highscoresbgtex;
	SDL_Texture *pretotex;
	SDL_Texture *brancotex;
	SDL_Texture *lifebar;
	SDL_Texture *howtopausetex;
	SDL_Texture *insertnametex;
	SDL_Texture *namescreentex;
	SDL_Texture *optionsmusictex;
	SDL_Texture *optionssoundtex;
	SDL_Texture *optionsgamemodetex;
	SDL_Texture *boom;
	SDL_Texture *pressspace;
	SDL_Texture *enemybullettex;
	SDL_Texture *derroteochefe;

}Texture;

typedef struct _arquivos
{
	FILE *p_arquivo;
}Arquivos;

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
	int frameboom;
	int cont;
	int dead;
	int rof;
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
	int danocolldown;
	int gamemode;
	int optionsroll;
	int musicvolume;
	int soundvolume;
	int mute;
	int enemyframe;

	
}Gamestate;

typedef struct _musics
{
	Mix_Music *menu;
	Mix_Music *boss;
	Mix_Music *game;
	Mix_Music *lose;
	Mix_Music *win;
}Musica;



typedef struct _sounds
{
	Mix_Chunk *arma1;
	Mix_Chunk *arma2;
	Mix_Chunk *arma3;
	Mix_Chunk *damage;
	Mix_Chunk *life;
	Mix_Chunk *speed;
	Mix_Chunk *playerdano;
	Mix_Chunk *reload;
	Mix_Chunk *enemydano;
	Mix_Chunk *menuroll;
	Mix_Chunk *menuenter;
	Mix_Chunk *boom;
	
}Sounds;

typedef struct
{
    char nome[MAX_NOME];
    int pontuacao;
} RECORDE;

typedef struct
{
    RECORDE vetor[MAX_ARRAY];
    int n;

} ARRAY;

Musica music;

Sounds sound;

Texture texture;

Arquivos arquivos;

Fontes font;

void loadimages(SDL_Renderer* renderer,Texture *texture);

void desenha(SDL_Renderer* renderer, Gamestate *gamestate,Texture *texture);

RECORDE elemento(ARRAY *, int);
int tamanho(ARRAY *);

void inserehighscore(ARRAY *, RECORDE);

void remove_posicao(ARRAY *, int);
void imprime(ARRAY *,SDL_Renderer**,Gamestate *);
void sort(ARRAY *);
void bubble_sort(RECORDE *, int);

ARRAY array;

