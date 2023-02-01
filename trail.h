#ifndef trail_h
#define trail_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "bike.h"

typedef struct Trail_type *Trail;

Trail createTrail(); 
void updateTrail(int x, int y, Trail theTrail, int current, int length);
bool trailHit(Hitbox h1, Trail theTrail);
void trailDraw(SDL_Renderer *rend, Trail theTrail, SDL_Surface *window_surface);
void removeTrail(Trail theTrail);
Hitbox trailHitbox(Trail t);

#endif