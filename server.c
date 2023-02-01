#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <string.h>
#include "bike.h"

struct Data_type{
    int gameStarted;
    int playerID;
    int alive[5];
    int angle[5];
    int xPos[5];
    int yPos[5];
}typedef Data;


int main(void){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDLNet_Init();

    IPaddress ip;
    SDLNet_ResolveHost(&ip, NULL, 42069);

    TCPsocket server = SDLNet_TCP_Open(&ip);

    TCPsocket client;

    int players = 1;
    Data *PlayerPositions = malloc(sizeof(1024));
    Data *tmp = malloc(sizeof(1024));
    char message[512];
    int gameStarted, playerID, alive, angle, x, y;
    int alive1,angle1,x1,y1,alive2,angle2,x2,y2,alive3,angle3,x3,y3;
    PlayerPositions->gameStarted = 0;

    for(int i=1;i<5;i++)
    {
        PlayerPositions->alive[i]=0;
    }
    
    while (1)
    {
        client = SDLNet_TCP_Accept(server);

        if (client != 0){

            // communicate with client and send PlayerPositions
            SDLNet_TCP_Recv(client,message, 512);
            sscanf(message,"%d %d %d %d %d %d",&gameStarted, &playerID, &alive, &angle, &x, &y );


            if(playerID == 0)
            {
                playerID = players;
                players++;
                sprintf(message, "%d", (int) playerID);
                SDLNet_TCP_Send(client, message, 512);
            }
            if(gameStarted==1)
            {
                PlayerPositions->gameStarted = 1;
            }
            if(playerID>4)
            {
                playerID=0;
            }
            PlayerPositions->alive[playerID]    = alive;
            PlayerPositions->angle[playerID]    = angle;   
            PlayerPositions->xPos[playerID]     = x;
            PlayerPositions->yPos[playerID]     = y;

            printf("Stored Xcord %d \n", PlayerPositions->xPos[1]);
            printf("Stored Ycord %d \n", PlayerPositions->yPos[1]);
            printf("Stored Xcord %d \n", PlayerPositions->xPos[2]);
            printf("Stored Ycord %d \n", PlayerPositions->yPos[2]);
            printf("Stored Xcord %d \n", PlayerPositions->xPos[3]);
            printf("Stored Ycord %d \n", PlayerPositions->yPos[3]);
            printf("\n \n \n");
            gameStarted = PlayerPositions->gameStarted;

            //// Sending Info About other players ////
            
            if(playerID == 1)
            {
                alive1  = PlayerPositions->alive[2];
                angle1  = PlayerPositions->angle[2];
                x1      = PlayerPositions->xPos[2];
                y1      = PlayerPositions->yPos[2];
                alive2  = PlayerPositions->alive[3];
                angle2  = PlayerPositions->angle[3];
                x2      = PlayerPositions->xPos[3];
                y2      = PlayerPositions->yPos[3];
                alive3  = PlayerPositions->alive[4];
                angle3  = PlayerPositions->angle[4];
                x3      = PlayerPositions->xPos[4];
                y3      = PlayerPositions->yPos[4];

                sprintf(message, "%d %d %d %d %d %d %d %d %d %d %d %d %d",(int)gameStarted, (int)alive1, (int)angle1, (int)x1, (int)y1, (int)alive2, (int)angle2, (int)x2, (int)y2, (int)alive3, (int)angle3, (int)x3, (int)y3);
                SDLNet_TCP_Send(client, message, 512);
            }
            if(playerID == 2)
            {

                alive1  = PlayerPositions->alive[1];
                angle1  = PlayerPositions->angle[1];
                x1      = PlayerPositions->xPos[1];
                y1      = PlayerPositions->yPos[1];
                alive2  = PlayerPositions->alive[3];
                angle2  = PlayerPositions->angle[3];
                x2      = PlayerPositions->xPos[3];
                y2      = PlayerPositions->yPos[3];
                alive3  = PlayerPositions->alive[4];
                angle3  = PlayerPositions->angle[4];
                x3      = PlayerPositions->xPos[4];
                y3      = PlayerPositions->yPos[4];

                sprintf(message, "%d %d %d %d %d %d %d %d %d %d %d %d %d",(int)gameStarted, (int)alive1, (int)angle1, (int)x1, (int)y1, (int)alive2, (int)angle2, (int)x2, (int)y2, (int)alive3, (int)angle3, (int)x3, (int)y3);
                SDLNet_TCP_Send(client, message, 512);

            }
            if(playerID == 3)
            {

                alive1  = PlayerPositions->alive[1];
                angle1  = PlayerPositions->angle[1];
                x1      = PlayerPositions->xPos[1];
                y1      = PlayerPositions->yPos[1];
                alive2  = PlayerPositions->alive[2];
                angle2  = PlayerPositions->angle[2];
                x2      = PlayerPositions->xPos[2];
                y2      = PlayerPositions->yPos[2];
                alive3  = PlayerPositions->alive[4];
                angle3  = PlayerPositions->angle[4];
                x3      = PlayerPositions->xPos[4];
                y3      = PlayerPositions->yPos[4];

                sprintf(message, "%d %d %d %d %d %d %d %d %d %d %d %d %d",(int)gameStarted, (int)alive1, (int)angle1, (int)x1, (int)y1, (int)alive2, (int)angle2, (int)x2, (int)y2, (int)alive3, (int)angle3, (int)x3, (int)y3);
                SDLNet_TCP_Send(client, message, 512);

            }
            if(playerID == 4)
            {

                alive1  = PlayerPositions->alive[1];
                angle1  = PlayerPositions->angle[1];
                x1      = PlayerPositions->xPos[1];
                y1      = PlayerPositions->yPos[1];
                alive2  = PlayerPositions->alive[2];
                angle2  = PlayerPositions->angle[2];
                x2      = PlayerPositions->xPos[2];
                y2      = PlayerPositions->yPos[2];
                alive3  = PlayerPositions->alive[3];
                angle3  = PlayerPositions->angle[3];
                x3      = PlayerPositions->xPos[3];
                y3      = PlayerPositions->yPos[3];

                sprintf(message, "%d %d %d %d %d %d %d %d %d %d %d %d %d",(int)gameStarted, (int)alive1, (int)angle1, (int)x1, (int)y1, (int)alive2, (int)angle2, (int)x2, (int)y2, (int)alive3, (int)angle3, (int)x3, (int)y3);
                SDLNet_TCP_Send(client, message, 512);

            }
            SDLNet_TCP_Close(client);
        }
    }
   

    SDLNet_TCP_Close(server);

    SDLNet_Quit();
    SDL_Quit();
}