#pragma once

void menu(SDL_Window** window, SDL_Renderer**renderer);

void opening(SDL_Window**,SDL_Renderer**,SDL_Event *, Gamestate *,APPSTATE*);

void options(SDL_Window** window, SDL_Renderer**renderer);

void highscores(SDL_Window** window, SDL_Renderer**renderer);

void credits(SDL_Window** window, SDL_Renderer**renderer);