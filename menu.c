#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "hitbox.h"
#include "menu.h"

struct Menu_type{
    int         mouse_x;
    int         mouse_y;
    int         whatButton;

    SDL_Rect    m_position;
    SDL_Rect    pos;
    SDL_Rect    writeIP;

    TTF_Font    *font;
    SDL_Color   textColor;

    Hitbox      mouse;
    Hitbox      buttons[2];

    SDL_Surface *image;
    SDL_Texture *tex;
    SDL_Texture *tex2;
    SDL_Texture *tex3;
    SDL_Texture *textIP;
};

Menu createMenu(SDL_Renderer *rend){
    Menu m = malloc(sizeof(struct Menu_type));

    m->pos.x = 441;
    m->pos.y = 290;
    m->pos.w = 400;
    m->pos.h = 99;

    m->m_position.x = 0;
    m->m_position.y = 0;
    m->m_position.w = 1;
    m->m_position.h = 1;

    m->writeIP.x = 506;
    m->writeIP.y = 320;
    m->writeIP.w = 373;
    m->writeIP.h = 47;

    m->mouse_x = 0;
    m->mouse_y = 0;
    m->whatButton = -1;

    m->textColor.r = 0;
    m->textColor.g = 255;
    m->textColor.b = 255;

    m->buttons[0] = createHitbox(441, 290, 400, 99, rend);
    m->buttons[1] = createHitbox(441, 410, 400, 99, rend);
    
    m->mouse = createHitbox(m->m_position.x, m->m_position.y, m->m_position.w, m->m_position.h, rend);

    //Bilderna
    m->image = SDL_LoadBMP("joinButton.bmp");

    if(!m->image)
    {
        printf("Failed to load image\n");
    }

    m->tex = SDL_CreateTextureFromSurface(rend, m->image);
    SDL_FreeSurface(m->image);
    if (!m->tex)
    {
        printf("error creating texture: %s\n", SDL_GetError());
    }

    m->image = SDL_LoadBMP("startButton.bmp");

    if(!m->image)
    {
        printf("Failed to load image\n");
    }

    m->tex2 = SDL_CreateTextureFromSurface(rend, m->image);
    SDL_FreeSurface(m->image);
    if (!m->tex2)
    {
        printf("error creating texture: %s\n", SDL_GetError());
    }

    m->image = SDL_LoadBMP("quitButton.bmp");

    if(!m->image)
    {
        printf("Failed to load image\n");
    }

    m->tex3 = SDL_CreateTextureFromSurface(rend, m->image);
    SDL_FreeSurface(m->image);
    if (!m->tex3)
    {
        printf("error creating texture: %s\n", SDL_GetError());
    }

    m->font = TTF_OpenFont("./fonts/8bitOperatorPlus8-Regular.ttf",32);

    return m;
}

void menuCheck(Menu theMenu, int *gameStarted, int *menuPage, bool *keep_window_open, bool *changeSong, SDL_Event e, SDL_Surface *image, SDL_Texture *image_tex, SDL_Renderer *rend)
{
    if(SDL_PollEvent(&e) > 0)
    {
        SDL_GetMouseState(&theMenu->mouse_x, &theMenu->mouse_y);
        hitboxUpdate(theMenu->mouse, theMenu->mouse_x, theMenu->mouse_y, 1, 1);
        theMenu->whatButton=-1;
        for(int i=0;i<2;i++)
        {
            if(isHit(theMenu->mouse, theMenu->buttons[i]))
            {
                theMenu->pos.y=290+i*120;
                switch(i)
                {
                    case 0: theMenu->whatButton=0; 
                    break;
                    case 1: theMenu->whatButton=1; 
                    break;
                    default:
                    break;
                }
                if(SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                {
                    switch(i)
                    {
                        case 0: *menuPage=1;
                        break;
                        case 1: *keep_window_open = false;
                        break;
                        default:
                        break;
                    }
                }
            }
        }
    }
    switch(theMenu->whatButton)
    {
        case 0: SDL_RenderCopyEx(rend, theMenu->tex, NULL, &theMenu->pos, 0, NULL, SDL_FLIP_NONE); 
        break;
        case 1: SDL_RenderCopyEx(rend, theMenu->tex3, NULL, &theMenu->pos, 0, NULL, SDL_FLIP_NONE); 
        break;
        default:
        break;
    }
}

void ipWindow(Menu theMenu, char IP[16], int *stringLength, int *menuPage, bool *keep_window_open, SDL_Event e, SDL_Renderer *rend)
{
    if(SDL_PollEvent(&e) > 0)
    {
        if(e.type==SDL_QUIT)
        {
            *keep_window_open = false;
        }
        
        switch (e.type)
        {
            case SDL_TEXTINPUT:
            strcat(IP, e.text.text);
            *stringLength++;
            break;
            case SDL_KEYDOWN:
            switch(e.key.keysym.scancode)
            {
                case SDL_SCANCODE_RETURN: 
                    *menuPage=2;
                break;
                case SDL_SCANCODE_BACKSPACE:
                *stringLength--; 
                IP[*stringLength]='\0';
                break;
            }
            case SDL_KEYUP:
            switch(e.key.keysym.scancode)
            {
                case SDL_SCANCODE_RETURN: 
                break;
                case SDL_SCANCODE_BACKSPACE: 
                break;
            }
        }
    }
    theMenu->image = TTF_RenderText_Solid(theMenu->font,IP,theMenu->textColor);

    theMenu->textIP = SDL_CreateTextureFromSurface(rend,theMenu->image);
    SDL_FreeSurface(theMenu->image);

    SDL_RenderCopyEx(rend, theMenu->textIP, NULL, &theMenu->writeIP, 0, NULL, SDL_FLIP_NONE);
}

void lobbyMenu(Menu theMenu, int *gameStarted, int *menuPage, bool *keep_window_open, bool *changeSong, SDL_Event e, SDL_Renderer *rend)
{
    if(SDL_PollEvent(&e) > 0)
    {
        SDL_GetMouseState(&theMenu->mouse_x, &theMenu->mouse_y);
        hitboxUpdate(theMenu->mouse, theMenu->mouse_x, theMenu->mouse_y, 1, 1);
        theMenu->whatButton=-1;
        for(int i=0;i<2;i++)
        {
            if(isHit(theMenu->mouse, theMenu->buttons[i]))
            {
                theMenu->pos.y=290+i*120;
                switch(i)
                {
                    case 0: theMenu->whatButton=0; 
                    break;
                    case 1: theMenu->whatButton=1; 
                    break;
                    default: 
                    break;
                }
                if(SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                {
                    switch(i)
                    {
                        case 0: *gameStarted=1;
                                *changeSong=true;
                        break;
                        case 1: *keep_window_open = false;
                        break;
                        default:
                        break;
                    }
                }
            }
        }
    }
    switch(theMenu->whatButton)
    {
        case 0: SDL_RenderCopyEx(rend, theMenu->tex2, NULL, &theMenu->pos, 0, NULL, SDL_FLIP_NONE); 
        break;
        case 1: SDL_RenderCopyEx(rend, theMenu->tex3, NULL, &theMenu->pos, 0, NULL, SDL_FLIP_NONE); 
        break;
        default:
        break;
    }
}