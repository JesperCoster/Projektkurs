#include "trail.h"
#include "bike.h"
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

struct Trail_type
{
    SDL_Surface *m_image;
    SDL_Texture *tex;
    SDL_Rect     m_position;

    Hitbox       h1;
};

PUBLIC Trail createTrail(SDL_Renderer *rend)
{
    Trail t = malloc(sizeof(struct Trail_type));

    t->m_image = SDL_LoadBMP("trail.bmp");

    if(!t->m_image)
    {
        printf("Failed to load image\n");
    }

    // load the image data into the graphics hardware's memory
    t->tex = SDL_CreateTextureFromSurface(rend, t->m_image);
    SDL_FreeSurface(t->m_image);
    if (!t->tex)
    {
        printf("error creating texture: %s\n", SDL_GetError());
    }

    t->m_position.x = -10;
    t->m_position.y = -10;
    t->m_position.w = 5;
    t->m_position.h = 5;

    t->h1 = createHitbox(t->m_position.x, t->m_position.y, 5, 5, rend);

    return t;
}

void updateTrail(int x, int y, Trail theTrail, int current, int length)
{
    theTrail->m_position.x=x+20;
    theTrail->m_position.y=y+8;
    hitboxUpdate(theTrail->h1, theTrail->m_position.x, theTrail->m_position.y, 5, 5);
}

bool trailHit(Hitbox h1, Trail theTrail)
{
    if(isHit(h1, theTrail->h1))
    {
        return true;
    }
    else 
    {
        return false;
    }
}

void trailDraw(SDL_Renderer *rend, Trail theTrail, SDL_Surface *window_surface)
{
        SDL_RenderCopyEx(rend, theTrail->tex, NULL, &theTrail->m_position, 0, NULL, SDL_FLIP_HORIZONTAL);
}   

void removeTrail(Trail theTrail)
{
    hitboxUpdate(theTrail->h1, 0, 0, 0, 0);
}

Hitbox trailHitbox(Trail t)
{
    return t->h1;
}