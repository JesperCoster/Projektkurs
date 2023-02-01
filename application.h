#ifndef application_h
#define application_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct Application_type *Application;

Application createApplication();
void applicationUpdate(Application theApp);
void menu(Application theApp, SDL_Event const e);
void destoryApplication(Application theApp);

#endif