#ifndef bike_h
#define bike_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "hitbox.h"
#include "sound.h"

typedef struct Bike_type *Bike;

Bike createBike();
void setStartPos(Bike theBike, int playerID);
void resetBike(Bike theBike);
void bikeUpdate(Bike theBike, Hitbox h1[4], Sound theSound, SDL_Renderer *rend, SDL_Surface *window_surface);
void bikeDraw(SDL_Renderer *rend, Bike theBike, int i, SDL_Surface *window_surface);
void bikeEventHandler(Bike theBike, SDL_Event const e);
void updateAngle(Bike theBike);
void trailCollide(Bike theBike[], Sound theSound);
Hitbox bikeHitbox(Bike b);
int getBikePosX(Bike theBike);
int getBikePosY(Bike theBike);
double getBikeAngle(Bike theBike);
int getBikePlayerID(Bike theBike);
int getBikeAlive(Bike theBike);
void updateFromServer(Bike theBike, int x, int y, int angle, int alive);
void killBike(Bike theBike, Sound theSound, int done);
void drawDeath(Bike theBike, SDL_Renderer *rend);

#endif
