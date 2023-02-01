#include "hitbox.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_rect.h>
#include <stdbool.h>
#include <math.h>

#define PUBLIC /* empty */
#define PRIVATE static

struct Hitbox_type{
    SDL_Rect rectangle;
};
PUBLIC Hitbox createHitbox(int xpos, int ypos, int width, int height, SDL_Renderer *rend){
    Hitbox h = malloc(sizeof(struct Hitbox_type));

    h->rectangle.x = xpos;
    h->rectangle.y = ypos;

    h->rectangle.w = width;
    h->rectangle.h = height;

    return h;
}

PUBLIC void hitboxUpdate(Hitbox h, int xpos, int ypos, int width, int height){
    h->rectangle.x = xpos;
    h->rectangle.y = ypos;

    h->rectangle.w = width;
    h->rectangle.h = height;
}

PUBLIC bool isHit(Hitbox h1, Hitbox h2){ 
    if (h1->rectangle.x + h1->rectangle.w < h2->rectangle.x ||
        h1->rectangle.x > h2->rectangle.x + h2->rectangle.w ||
        h1->rectangle.y + h1->rectangle.h < h2->rectangle.y ||
        h1->rectangle.y > h2->rectangle.y + h2->rectangle.h
    )
    {
        // no colission
        return false;
    }
    else{
        return true;
    }
}

PUBLIC bool hitDiagonal(Hitbox h1){ 
    if (h1->rectangle.y < -0.526*h1->rectangle.x+364 ||
        h1->rectangle.y+h1->rectangle.h > 0.471*h1->rectangle.x+436 ||
        h1->rectangle.y < 0.488*(h1->rectangle.x+h1->rectangle.w)-276 ||
        h1->rectangle.y+h1->rectangle.h > -0.522*(h1->rectangle.x+h1->rectangle.w)+1090
    )
    {
        // no colission
        return true;
    }
    else{
        return false;
    }
}