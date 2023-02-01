#ifndef hitbox_h
#define hitbox_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

typedef struct Hitbox_type *Hitbox;

Hitbox createHitbox(int xpos, int ypos, int width, int height, SDL_Renderer *rend);
void hitboxUpdate(Hitbox h, int xpos, int ypos, int width, int height);
bool isHit(Hitbox h1, Hitbox h2);
bool hitDiagonal(Hitbox h1);

#endif
