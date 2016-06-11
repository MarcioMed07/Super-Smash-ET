#pragma once


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

typedef struct _salasstruct
{
	int x,y,w,h;
	int enemytype1;
	int enemytype2;
	int enemytype3;
	int enemytypeboss;
	int wave;
	int clear;
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
} Player;

typedef struct _parede
{
	int x,y,w,h;
}Parede;

typedef struct _textures
{
	SDL_Texture *backgroundtex;
	SDL_Texture *playertex;
	SDL_Texture *mousetex;
	SDL_Texture *bullettex;
	SDL_Texture *enemytex;
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
	
}Gamestate;

Texture texture;

void loadimages(SDL_Renderer* renderer,Texture *texture);

void desenha(SDL_Renderer* renderer, Gamestate *gamestate,Texture *texture);
