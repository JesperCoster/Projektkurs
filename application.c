#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include "application.h"
#include "bike.h"
#include "hitbox.h"
#include "trail.h"
#include "menu.h"
#include "sound.h"
#include "client.h"

#define PUBLIC /* empty */
#define PRIVATE static
#define PLAYERS (4)

struct Application_type{
    // Window variables
    SDL_Window   *window;
    SDL_Surface  *window_surface;
    SDL_Event     window_event;
    SDL_Surface  *image;
    SDL_Texture  *image_tex[6];
    SDL_Renderer *rend;

    SDL_Texture  *tex;

    // Client network
    Client clientNet;
    Data dataNet;
    Data *tmp;

    bool          keep_window_open;
    int           gameStarted;
    int           menuPage;
    char          IP[16];
    int           stringLength;
    int           isGameStarted;

    // Game objects
    Bike player[PLAYERS];
    int playersAlive;
    bool changeSong;

    Hitbox mapBoxes[4];

    Menu theMenu;

    Sound theSound;
};

PRIVATE void update(Application theApp, double delta_time);
PRIVATE void draw(Application theApp);

PUBLIC Application createApplication(){
    Application s = malloc(sizeof(struct Application_type));
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("Failed to initialize the SDL2 library\n");
    }

    if(TTF_Init()<0)
    {
        printf("Failed to initialize the SDL2 TTF\n");
    }

    s->window= SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1280, 720,
                                          0);

    if(!s->window)
    {
        printf("Failed to create window\n");
    }

    if ( SDLNet_Init() < 0 ) 
    {
	    printf("Failed to initialize the SDL2 net\n");
    }

    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    s->rend = SDL_CreateRenderer(s->window, -1, render_flags);
    if (!s->rend)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(s->window);
        SDL_Quit();
    }

    s->window_surface = SDL_GetWindowSurface(s->window);

    if(!s->window_surface)
    {
        printf("Failed to get the surface from the window\n"); 
    }

    // Load bitmap
    s->image = SDL_LoadBMP("menu.bmp");

    if(!s->image)
    {
        printf("Failed to load image\n");
    }

    // load the image data into the graphics hardware's memory
    s->image_tex[0] = SDL_CreateTextureFromSurface(s->rend, s->image);
    SDL_FreeSurface(s->image);
    if (!s->image_tex[0])
    {
        printf("error creating texture: %s\n", SDL_GetError());
    }

    s->image = SDL_LoadBMP("map.bmp");

    if(!s->image)
    {
        printf("Failed to load image\n");
    }

    // load the image data into the graphics hardware's memory
    s->image_tex[1] = SDL_CreateTextureFromSurface(s->rend, s->image);
    SDL_FreeSurface(s->image);
    if (!s->image_tex[1])
    {
        printf("error creating texture: %s\n", SDL_GetError());
    }

    s->image = SDL_LoadBMP("enterIp.bmp");

    if(!s->image)
    {
        printf("Failed to load image\n");
    }

    // load the image data into the graphics hardware's memory
    s->image_tex[2] = SDL_CreateTextureFromSurface(s->rend, s->image);
    SDL_FreeSurface(s->image);
    if (!s->image_tex[2])
    {
        printf("error creating texture: %s\n", SDL_GetError());
    }

    s->image = SDL_LoadBMP("start.bmp");

    if(!s->image)
    {
        printf("Failed to load image\n");
    }

    // load the image data into the graphics hardware's memory
    s->image_tex[3] = SDL_CreateTextureFromSurface(s->rend, s->image);
    SDL_FreeSurface(s->image);
    if (!s->image_tex[3])
    {
        printf("error creating texture: %s\n", SDL_GetError());
    }

    s->image = SDL_LoadBMP("victory.bmp");

    if(!s->image)
    {
        printf("Failed to load image\n");
    }

    // load the image data into the graphics hardware's memory
    s->image_tex[4] = SDL_CreateTextureFromSurface(s->rend, s->image);
    SDL_FreeSurface(s->image);
    if (!s->image_tex[4])
    {
        printf("error creating texture: %s\n", SDL_GetError());
    }

    s->image = SDL_LoadBMP("youSuck.bmp");

    if(!s->image)
    {
        printf("Failed to load image\n");
    }

    // load the image data into the graphics hardware's memory
    s->image_tex[5] = SDL_CreateTextureFromSurface(s->rend, s->image);
    SDL_FreeSurface(s->image);
    if (!s->image_tex[5])
    {
        printf("error creating texture: %s\n", SDL_GetError());
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    
    s->gameStarted = 0;
    s->menuPage = 0;
    s->stringLength = 0;
    s->keep_window_open = true;
    s->changeSong = true;
    s->isGameStarted = 0;
    for(int i=0;i<16;i++)
    {
        s->IP[i]='\0';
    }

    s->player[0] = createBike(386, 235, 1, s->rend);  
    s->player[1] = createBike(886, 534, 2, s->rend);   
    s->player[2] = createBike(386, 534, 3, s->rend);   
    s->player[3] = createBike(886, 235, 4, s->rend); 
    s->theMenu = createMenu(s->rend);
    s->theSound = initSound();

    s->clientNet = createClient();
    for(int i=0; i<4; i++)
    {
        s->dataNet = createData();
        s->tmp = createData();
    }
    

    s->mapBoxes[0] = createHitbox(0, 0, 1280, 140, s->rend);
    s->mapBoxes[1] = createHitbox(1137, 0, 142, 720, s->rend);
    s->mapBoxes[2] = createHitbox(0, 647, 1280, 73, s->rend);
    s->mapBoxes[3] = createHitbox(0, 0, 147, 720, s->rend);

    return s;
}

PUBLIC void applicationUpdate(Application theApp){

    int i = 0, wait = 0, runNet = 0;
    int x, y, angle, playerID, alive, win;
    setID(theApp->dataNet);
    while(theApp->keep_window_open)
    {   
        if(theApp->gameStarted==0)
        {
            SDL_RenderClear(theApp->rend);
            switch(theApp->menuPage)
            {
                case 0: SDL_RenderCopy(theApp->rend, theApp->image_tex[0], NULL, NULL);
                        menuCheck(theApp->theMenu, &theApp->gameStarted, &theApp->menuPage, &theApp->keep_window_open, &theApp->changeSong, theApp->window_event, theApp->image, theApp->image_tex, theApp->rend);
                break;
                case 1: SDL_RenderCopy(theApp->rend, theApp->image_tex[2], NULL, NULL);
                        ipWindow(theApp->theMenu, theApp->IP, &theApp->stringLength, &theApp->menuPage, &theApp->keep_window_open, theApp->window_event, theApp->rend);
                break;
                case 2: SDL_RenderCopy(theApp->rend, theApp->image_tex[3], NULL, NULL);
                        lobbyMenu(theApp->theMenu, &theApp->gameStarted, &theApp->menuPage, &theApp->keep_window_open, &theApp->changeSong, theApp->window_event, theApp->rend);
                        if(runNet==8)
                        {
                            initNetwork(theApp->clientNet, theApp->IP);
                            sendRecv(theApp->clientNet, theApp->dataNet, x, y, angle, playerID, alive, theApp->gameStarted);
                            theApp->gameStarted = getDataGameStarted(theApp->dataNet);
                            playerID = getDataPlayerID(theApp->dataNet, i);
                            setStartPos(theApp->player[0], playerID);
                            runNet=0;
                        }
                        runNet++;
                break;
            }
        }

        if(theApp->gameStarted==1)
        {
            while(SDL_PollEvent(&theApp->window_event) > 0)
            {   
                SDL_Event test = theApp->window_event;
                
                bikeEventHandler(theApp->player[0], theApp->window_event);
                
                switch(theApp->window_event.type)
                {
                    case SDL_QUIT:
                        theApp->keep_window_open = false;
                        break;
                }
            }
            if(runNet==4)
            {
                //get data from bike
                x           = getBikePosX(theApp->player[0]);
                y           = getBikePosY(theApp->player[0]);
                angle       = getBikeAngle(theApp->player[0]);
                playerID    = getBikePlayerID(theApp->player[0]);
                alive       = getBikeAlive(theApp->player[0]);

                //Send/Recive data from server
                initNetwork(theApp->clientNet, theApp->IP);
                sendRecv(theApp->clientNet, theApp->dataNet, x, y, angle, playerID, alive, theApp->gameStarted);

                //Then close connection
                closeTCPconnection(theApp->clientNet);

                //// Update other players values ////
                for(int i = 1; i<4; i++)
                {
                    x           = getDatax(theApp->dataNet, i);
                    y           = getDatay(theApp->dataNet, i);
                    angle       = getDataAngle(theApp->dataNet, i);
                    playerID    = getDataPlayerID(theApp->dataNet, i);
                    alive       = getDataAlive(theApp->dataNet, i);

                    if(alive==0)
                    {
                        killBike(theApp->player[i], theApp->theSound, 0);                        
                    }

                    //Then Update players in game
                    
                    updateFromServer(theApp->player[i], x, y, angle, alive);
                }
                runNet=0;
            }
            runNet++;
            
            trailCollide(theApp->player, theApp->theSound);
            for(int i=0;i<4;i++)
            {
                bikeUpdate(theApp->player[i], theApp->mapBoxes, theApp->theSound, theApp->rend, theApp->window_surface);
            }

            SDL_RenderClear(theApp->rend);

            SDL_RenderCopy(theApp->rend, theApp->image_tex[1], NULL, NULL);

            // draw the image to the window
            for(int i=0;i<4;i++)
            {
                bikeDraw(theApp->rend, theApp->player[i], i, theApp->window_surface);
                drawDeath(theApp->player[i], theApp->rend);
            }

            theApp->playersAlive=0;
            for(int i=0;i<4;i++)
            {
                theApp->playersAlive+=getBikeAlive(theApp->player[i]);
            }

            if(theApp->playersAlive<=1 && getBikeAlive(theApp->player[0]))
            {
                SDL_RenderCopy(theApp->rend, theApp->image_tex[4], NULL, NULL);
                win=1;
                wait++;
            }
            else if(theApp->playersAlive<=1 && win!=1)
            {
                SDL_RenderCopy(theApp->rend, theApp->image_tex[5], NULL, NULL);
                wait++;
            }
        }
        playSound(theApp->theSound, &theApp->changeSong, theApp->gameStarted);

        SDL_RenderPresent(theApp->rend);

        if(wait==300)
            {
                wait=0;
                win=0;
                theApp->gameStarted = 0;
                theApp->menuPage = 0;
                theApp->changeSong = true;

                resetBike(theApp->player[0]);
                resetBike(theApp->player[1]);
                resetBike(theApp->player[2]);
                resetBike(theApp->player[3]);

                for(int i=0;i<16;i++)
                {
                    theApp->IP[i]='\0';
                }
            }
        
        // wait 1/60th of a second
        SDL_Delay(1000/30);

    }
}

PRIVATE void draw(Application theApp)
{
    SDL_UpdateWindowSurface(theApp->window);
}

PUBLIC void destoryApplication(Application theApp)
{
    freeSound(theApp->theSound);
    SDL_FreeSurface(theApp->window_surface);
    SDL_DestroyWindow(theApp->window);
    Mix_Quit();
    SDLNet_Quit();
    SDL_Quit();
}

