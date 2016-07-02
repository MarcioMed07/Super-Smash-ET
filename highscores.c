#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "main.h"




RECORDE elemento(ARRAY *array, int posicao)
{
	return array->vetor[posicao];
}

int tamanho(ARRAY *array)
{
	return array->n;
}

void inserehighscore(ARRAY *array, RECORDE recorde)
{
    if(tamanho(array) < MAX_ARRAY)
    {
        array->vetor[tamanho(array)] = recorde;
        array->n += 1;
    }
    else
    {
        RECORDE menor_recorde;
        menor_recorde = elemento(array, MAX_ARRAY - 1);
        
        if(menor_recorde.pontuacao >= recorde.pontuacao)
        {
            return;
        }
        else
        {
            remove_posicao(array, MAX_ARRAY - 1);
            inserehighscore(array, recorde);
            return;
        }
    }
    
    sort(array);
}

void remove_posicao(ARRAY *array, int posicao)
{
	if(tamanho(array) == 0)
	{
		return;
	}
	else if(tamanho(array) == 1)
	{
		array->n -= 1;
		return;
	}
	else
	{
		array->n -= 1;
		array->vetor[posicao] = array->vetor[tamanho(array)];
	}
    
    sort(array);
}

void imprime(ARRAY *array,SDL_Renderer **renderer,Gamestate *gamestate)
{
	int i;
    RECORDE recorde;

    strcpy(recorde.nome, gamestate->player.name);
	recorde.pontuacao = gamestate->player.score;

	for(i = 0; i < tamanho(array) ; i++)
	{
		sort(array);

        char linhascore[100];

        recorde = elemento(array, i);

        sprintf(linhascore,"%d - %05d :: %s \n", i+1, recorde.pontuacao, recorde.nome);

        SDL_Rect highscoreRect = {(1366/2) - 230,120 + (55 * (i + 2)), (20*strlen(linhascore)) , 40};
        

        SDL_Color branco = {255,255,255, SDL_ALPHA_OPAQUE};
	    SDL_Surface* highscoresSurface = TTF_RenderText_Solid(font.scoretela,linhascore,branco);		
		texture.highscorestex = SDL_CreateTextureFromSurface( *renderer, highscoresSurface );	
		SDL_FreeSurface(highscoresSurface);
		SDL_RenderCopy(*renderer, texture.highscorestex, NULL, &highscoreRect);
	}

}

void sort(ARRAY *array)
{
	bubble_sort(array->vetor, array->n);
}

void bubble_sort(RECORDE list[], int n)
{
	int i, j;
    RECORDE swap;

	for(i = 0 ; i < ( n - 1 ); i++)
	{
		for(j = 0 ; j < n - i - 1; j++)
		{
			if(list[j].pontuacao < list[j+1].pontuacao)
			{ 
				swap = list[j];
				list[j] = list[j+1];
				list[j+1] = swap;
			}
		}
	}
}







void highscores(SDL_Window** window, SDL_Renderer**renderer,Gamestate *gamestate)
{

	SDL_RenderCopy(*renderer, texture.highscoresbgtex,NULL, NULL);
	SDL_SetRenderDrawColor(*renderer, 0, 0,0, 0);

	char *nome_arquivo = "recordes.dat";
    

    

    if((arquivos.p_arquivo = fopen(nome_arquivo, "r")) != NULL)
    {
        fread(&array, sizeof(ARRAY), 1, arquivos.p_arquivo);
        fclose(arquivos.p_arquivo);
    }

    //imprime(&array);

    /*RECORDE rec1;
    

    strcpy(rec1.nome, gamestate->player.name);

    rec1.nome[strlen(rec1.nome) - 1] = '\0';

   	rec1.pontuacao = gamestate->player.score;

    inserehighscore(&array, rec1);*/
    sort(&array);

    imprime(&array, renderer,gamestate);

   

    

	
	

	/*

	SDL_Rect scoretelaRect = {383,220,600 , 40};
	SDL_Color branco = {255,255,255, SDL_ALPHA_OPAQUE};
	char str[50];
	printf("%s\n",str );	
	SDL_Surface* scoretelaSurface = TTF_RenderText_Solid(font.scoretela,str,branco);		
	texture.scoretela = SDL_CreateTextureFromSurface( *renderer, scoretelaSurface );	
	SDL_FreeSurface(scoretelaSurface);
	SDL_RenderCopy(*renderer, texture.scoretela, NULL, &scoretelaRect);*/


	SDL_RenderPresent(*renderer);
	SDL_RenderClear(*renderer);  

	//fclose(recordes);

	

}