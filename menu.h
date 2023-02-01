#ifndef menu_h
#define menu_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef struct Menu_type *Menu;

Menu createMenu(SDL_Renderer *rend);
void menuCheck(Menu theMenu, int *gameStarted, int *menuPage, bool *keep_window_open, bool *changeSong, SDL_Event const e, SDL_Surface *image, SDL_Texture *image_tex, SDL_Renderer *rend);
void ipWindow(Menu theMenu, char IP[], int *stringLength, int *menuPage, bool *keep_window_open, SDL_Event const e, SDL_Renderer *rend);
void lobbyMenu(Menu theMenu, int *gameStarted, int *menuPage, bool *keep_window_open, bool *changeSong, SDL_Event e, SDL_Renderer *rend);

#endif