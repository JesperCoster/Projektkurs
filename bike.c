#include "bike.h"
#include "trail.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_rect.h>
#include <stdbool.h>
#include <math.h>
#include "hitbox.h"
#include "sound.h"

#define PUBLIC /* empty */
#define PRIVATE static

// speed in pixels/second
#define SPEED (300)
#define TRAILMAX (500)

struct Bike_type{
    SDL_Surface *m_image;
    SDL_Texture *tex[4];
    SDL_Texture *texdeath1;
    SDL_Texture *texdeath2;
    SDL_Texture *texdeath3;
    SDL_Texture *texdeath4;
    SDL_Rect     m_position;
    SDL_Rect     explosion;
    SDL_Point    rotationPoint;
    SDL_Point    invRotationPoint;

    double       angle;

    int          steplength;
    double       turningSpeed;

    bool         left;
    bool         right;
    bool         haveTurned;
    int          turnTimer;

    Hitbox       h1;

    Trail        trail[TRAILMAX];
    int          trailLength;
    int          currentTrail;
    int          timer;
    int          playerID;

    bool         alive;
    int          deathAnimation;
};

PUBLIC Bike createBike(int x, int y, int selectedBike, SDL_Renderer *rend){
    Bike b = malloc(sizeof(struct Bike_type));

    b->m_image = SDL_LoadBMP("bike.bmp");
    
    if(!b->m_image)
    {
        printf("Failed to load image\n");
    }

    // load the image data into the graphics hardware's memory
    b->tex[0] = SDL_CreateTextureFromSurface(rend, b->m_image);
    SDL_FreeSurface(b->m_image);
    if (!b->tex[0])
    {
        printf("error creating texture: %s\n", SDL_GetError());
    }

    b->m_image = SDL_LoadBMP("bike2.bmp");
    
    if(!b->m_image)
    {
        printf("Failed to load image\n");
    }

    // load the image data into the graphics hardware's memory
    b->tex[1] = SDL_CreateTextureFromSurface(rend, b->m_image);
    SDL_FreeSurface(b->m_image);
    if (!b->tex[1])
    {
        printf("error creating texture: %s\n", SDL_GetError());
    }

    b->m_image = SDL_LoadBMP("bike3.bmp");
    
    if(!b->m_image)
    {
        printf("Failed to load image\n");
    }

    // load the image data into the graphics hardware's memory
    b->tex[2] = SDL_CreateTextureFromSurface(rend, b->m_image);
    SDL_FreeSurface(b->m_image);
    if (!b->tex[2])
    {
        printf("error creating texture: %s\n", SDL_GetError());
    }

    b->m_image = SDL_LoadBMP("bike4.bmp");
    
    if(!b->m_image)
    {
        printf("Failed to load image\n");
    }

    // load the image data into the graphics hardware's memory
    b->tex[3] = SDL_CreateTextureFromSurface(rend, b->m_image);
    SDL_FreeSurface(b->m_image);
    if (!b->tex[3])
    {
        printf("error creating texture: %s\n", SDL_GetError());
    }

    b->m_image = SDL_LoadBMP("explosion1.bmp");
    
    if(!b->m_image)
    {
        printf("Failed to load image1\n");
    }

    // load the image data into the graphics hardware's memory
    b->texdeath1 = SDL_CreateTextureFromSurface(rend, b->m_image);
    SDL_FreeSurface(b->m_image);
    if (!b->texdeath1)
    {
        printf("error creating texture: %s\n", SDL_GetError());
    }

    b->m_image = SDL_LoadBMP("explosion2.bmp");
    
    if(!b->m_image)
    {
        printf("Failed to load image2\n");
    }

    // load the image data into the graphics hardware's memory
    b->texdeath2 = SDL_CreateTextureFromSurface(rend, b->m_image);
    SDL_FreeSurface(b->m_image);
    if (!b->texdeath2)
    {
        printf("error creating texture: %s\n", SDL_GetError());
    }

    b->m_image = SDL_LoadBMP("explosion3.bmp");
    
    if(!b->m_image)
    {
        printf("Failed to load image3\n");
    }

    // load the image data into the graphics hardware's memory
    b->texdeath3 = SDL_CreateTextureFromSurface(rend, b->m_image);
    SDL_FreeSurface(b->m_image);
    if (!b->texdeath3)
    {
        printf("error creating texture: %s\n", SDL_GetError());
    }

    b->m_image = SDL_LoadBMP("explosion4.bmp");
    
    if(!b->m_image)
    {
        printf("Failed to load image4\n");
    }

    // load the image data into the graphics hardware's memory
    b->texdeath4 = SDL_CreateTextureFromSurface(rend, b->m_image);
    SDL_FreeSurface(b->m_image);
    if (!b->texdeath4)
    {
        printf("error creating texture: %s\n", SDL_GetError());
    }

    b->explosion.w = 32;
    b->explosion.h = 32;

    b->m_position.x = x;
    b->m_position.y = y;
    b->m_position.w = 44;
    b->m_position.h = 20;
    b->angle = 0;

    b->h1 = createHitbox(b->m_position.x+33, b->m_position.y+4, 10, 12, rend);

    b->left = 0;
    b->right = 0;
    b->haveTurned = 0;
    b->turnTimer = 0;

    b->rotationPoint.x = 24;
    b->rotationPoint.y = 80;

    b->invRotationPoint.x = 40;
    b->invRotationPoint.y = 9;

    b->steplength = 3;
    b->turningSpeed = 45;


    for(int i=0;i<TRAILMAX;i++)
    {
        b->trail[i] = createTrail(rend);
    }
    b->trailLength = 35;
    b->currentTrail = 0;
    b->timer = 0;
    b->playerID = selectedBike-1;

    b->alive = 1;  
    b->deathAnimation = 0;

    return b;
}

void setStartPos(Bike theBike, int playerID)
{
    switch(playerID)
    {
        case 1: theBike->m_position.x=386;
                theBike->m_position.y=235;
                theBike->angle=45;
        break;
        case 2: theBike->m_position.x=886;
                theBike->m_position.y=534;
                theBike->angle=225;
        break;
        case 3: theBike->m_position.x=386;
                theBike->m_position.y=534;
                theBike->angle=315;
        break;
        case 4: theBike->m_position.x=886;
                theBike->m_position.y=235;
                theBike->angle=135;
        break;
    }
}

void resetBike(Bike theBike)
{
    for(int i=0;i<theBike->trailLength;i++)
    {
        removeTrail(theBike->trail[i]);
    }
    for(int i=0;i<theBike->trailLength;i++)
    {
        updateTrail(-50, -50, theBike->trail[i], i, theBike->trailLength);
    }
    theBike->left = 0;
    theBike->right = 0;
    theBike->haveTurned = 0;
    theBike->turnTimer = 0;
    theBike->trailLength = 35;
    theBike->currentTrail = 0;
    theBike->timer = 0;
    theBike->alive = 1;  
    theBike->deathAnimation = 0;
}

PUBLIC void bikeUpdate(Bike theBike, Hitbox h1[4], Sound theSound, SDL_Renderer *rend, SDL_Surface *window_surface){
    if(theBike->alive == 1)
    {
        updateTrail(theBike->m_position.x, theBike->m_position.y, theBike->trail[theBike->currentTrail], theBike->currentTrail, theBike->trailLength);

        theBike->currentTrail+=1;
        theBike->timer+=1;
        if(theBike->timer==10)
        {
            theBike->timer=0;
            if(theBike->trailLength<TRAILMAX)
            {   
                theBike->trailLength+=1;
            }
        }
        if(theBike->currentTrail==theBike->trailLength) 
        { 
            theBike->currentTrail=0;
        }
        updateAngle(theBike);
        if(theBike->playerID==0)
        {
            for(int i=0;i<4;i++)
            {
                if (isHit(h1[i], theBike->h1)){ killBike(theBike, theSound, 0); }
            }
            if (hitDiagonal(theBike->h1)){ killBike(theBike, theSound, 0); }
        }
    }
}

PUBLIC void bikeDraw(SDL_Renderer *rend, Bike theBike, int i, SDL_Surface *window_surface){
    if(theBike->alive)
    {
        for(int i=0;i<theBike->trailLength;i++)
        {
            trailDraw(rend, theBike->trail[i], window_surface);
        }
        SDL_RenderCopyEx(rend, theBike->tex[i], NULL, &theBike->m_position, (theBike->angle), NULL, SDL_FLIP_HORIZONTAL);
    }
}

PUBLIC void bikeEventHandler(Bike theBike, SDL_Event const e){
    if(theBike->alive)
    {
        switch (e.type)
        {
        case SDL_KEYDOWN:
            switch (e.key.keysym.scancode)
            {
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    theBike->left = 1;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    theBike->right = 1;
                    break;
            }
            break;
        case SDL_KEYUP:
            switch (e.key.keysym.scancode)
            {
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    theBike->left = 0;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    theBike->right = 0;
                    break;
            }
            break; 
        }
    }
}

PUBLIC void updateAngle(Bike theBike)
{
    //resets angle when it reaches 360/-360
    if (theBike->angle >= 360)    { theBike->angle = 0; }
    if (theBike->angle <= -45) { theBike->angle = 315; }

    //Inputs increase/ decrease the angle of the bike
    if (theBike->left && !theBike->right && theBike->haveTurned == 0 && theBike->turnTimer<=8) 
    {
        theBike->angle -= theBike->turningSpeed;
        theBike->haveTurned = 1;
        theBike->turnTimer = 0;
    }
    if (theBike->right && !theBike->left && theBike->haveTurned == 0 && theBike->turnTimer<=8) 
    {
        theBike->angle += theBike->turningSpeed;
        theBike->haveTurned = 1;
        theBike->turnTimer = 0;
    }
    
    if (theBike->turnTimer<8)
    {
        theBike->turnTimer++;
    }
    else
    {
        theBike->haveTurned = 0;
    }

    
    theBike->m_position.x += (int) round(theBike->steplength*cos((theBike->angle)/180*M_PI));
    theBike->m_position.y += (int) round(theBike->steplength*sin((theBike->angle)/180*M_PI));

    switch((int) theBike->angle)
    {
        case 0: hitboxUpdate(theBike->h1, theBike->m_position.x+33, theBike->m_position.y+4, 10, 12);
        break;
        case 45: hitboxUpdate(theBike->h1, theBike->m_position.x+28, theBike->m_position.y+16, 10, 10); 
        break;
        case 90: hitboxUpdate(theBike->h1, theBike->m_position.x+16, theBike->m_position.y+22, 12, 9);
        break;
        case 135: hitboxUpdate(theBike->h1, theBike->m_position.x+6, theBike->m_position.y+16, 10, 10);
        break;
        case 180: hitboxUpdate(theBike->h1, theBike->m_position.x, theBike->m_position.y+4, 10, 12);
        break;
        case 225: hitboxUpdate(theBike->h1, theBike->m_position.x+6, theBike->m_position.y-6, 10, 10);
        break;
        case 270: hitboxUpdate(theBike->h1, theBike->m_position.x+16, theBike->m_position.y-12, 12, 9);
        break;
        case 315: hitboxUpdate(theBike->h1, theBike->m_position.x+28, theBike->m_position.y-6, 10, 10);
        break;
    }
}

PUBLIC void trailCollide(Bike theBike[], Sound theSound)
{
    for(int j=0;j<3;j++)
    {
        for(int i=0;i<theBike[j]->trailLength;i++)
        {
            if(trailHit(theBike[0]->h1, theBike[j]->trail[i])){ killBike(theBike[0], theSound, 0); }
        }
    }
}

PUBLIC void updateFromServer(Bike theBike,int x,int y, int angle, int alive)
{
    theBike->m_position.x   = x;
    theBike->m_position.y   = y;
    theBike->angle          = angle;
    theBike->alive          = alive;
}

PUBLIC void killBike(Bike theBike, Sound theSound, int done)
{
    if(theBike->alive)
    {
        theBike->alive = 0;
        hitboxUpdate(theBike->h1, 0, 0, 0, 0);
        if(done==0)
        {
            playSoundEffect(theSound);
            theBike->deathAnimation = 1;
        }
        for(int i=0;i<theBike->trailLength;i++)
        {
            removeTrail(theBike->trail[i]);
        }
    }
}

PUBLIC void drawDeath(Bike theBike, SDL_Renderer *rend)
{
    if(theBike->deathAnimation>0 && theBike->deathAnimation<=40)
    {
        theBike->explosion.x=theBike->m_position.x+6;
        theBike->explosion.y=theBike->m_position.y;
        if(theBike->deathAnimation<10)
        {
            SDL_RenderCopyEx(rend, theBike->texdeath1, NULL, &theBike->explosion, 0, NULL, SDL_FLIP_NONE);
        }
        else if(theBike->deathAnimation<20)
        {
            SDL_RenderCopyEx(rend, theBike->texdeath2, NULL, &theBike->explosion, 0, NULL, SDL_FLIP_NONE);
        }
        else if(theBike->deathAnimation<30)
        {
            SDL_RenderCopyEx(rend, theBike->texdeath3, NULL, &theBike->explosion, 0, NULL, SDL_FLIP_NONE);
        }
        else 
        {
            SDL_RenderCopyEx(rend, theBike->texdeath4, NULL, &theBike->explosion, 0, NULL, SDL_FLIP_NONE);
        }
        theBike->deathAnimation = theBike->deathAnimation+1;
    }
}

PUBLIC Hitbox bikeHitbox(Bike b){
    return b->h1;
}

PUBLIC int getBikePosX(Bike theBike)
{
    return theBike->m_position.x;
}

PUBLIC int getBikePosY(Bike theBike)
{
    return theBike->m_position.y;
}

PUBLIC double getBikeAngle(Bike theBike)
{
    return theBike->angle;
}

PUBLIC int getBikePlayerID(Bike theBike)
{
    return theBike->playerID;
}

PUBLIC int getBikeAlive(Bike theBike)
{
    return theBike->alive;
}