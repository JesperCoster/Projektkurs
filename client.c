#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <string.h>
#include "client.h"
#include "bike.h"

#define PUBLIC /* empty */
#define PRIVATE static

struct Client_type{
    IPaddress ip;

    TCPsocket client;
    char* msg;
    char* receivedMsg[100];
};
struct Data_type{
    int gameStarted;
    int playerID;
    int alive[5];
    int angle[5];
    int xPos[5];
    int yPos[5];
};

PUBLIC Client createClient(){
    Client c = malloc(sizeof(struct Client_type));

    c->msg = "this is game! \n";

    return c;
}
PUBLIC Data createData(){

    Data d = malloc(sizeof(struct Data_type));

    return d;
}

void initNetwork(Client theClient, char ip[16])
{
    SDLNet_ResolveHost(&(theClient->ip), ip, 42069);

    theClient->client = SDLNet_TCP_Open(&(theClient->ip));
}

void sendRecv(Client theClient, Data data, int x, int y, int angle, int playerID, int alive, int gameStarted)
{
    char message[600];
    playerID = data->playerID;

    sprintf(message, "%d %d %d %d %d %d",(int)gameStarted, (int)playerID, (int)alive, (int)angle, (int)x, (int)y);
    

    SDLNet_TCP_Send(theClient->client, message, 512);
    //If player has not been assigned an ID, get ID

    if(data->playerID == 0)
    {
        SDLNet_TCP_Recv(theClient->client, message, 512);
        sscanf(message, "%d", &playerID);
        data->playerID = playerID;
    }

    //// Reciving other players info ////
    SDLNet_TCP_Recv(theClient->client, message, 512);
    sscanf(message,"%d %d %d %d %d %d %d %d %d %d %d %d %d", &data->gameStarted, &data->alive[1], &data->angle[1], &data->xPos[1], &data->yPos[1], &data->alive[2], &data->angle[2], &data->xPos[2], &data->yPos[2], &data->alive[3], &data->angle[3], &data->xPos[3], &data->yPos[3]);
}
void closeTCPconnection(Client theClient){
    SDLNet_TCP_Close(theClient->client);
}
void setID(Data data)
{
    for(int i=1;i<5;i++)
    {
        data->alive[i]=0;
    }
    data->playerID = 0;
}
int getDatax(Data data, int i)
{
    return data->xPos[i];
}
int  getDatay(Data data, int i)
{
    return data->yPos[i];
}
int getDataAngle(Data data, int i)
{
    return data->angle[i];
}
int getDataPlayerID(Data data, int i)
{
    return data->playerID;
}
int getDataAlive(Data data, int i)
{
    return data->alive[i];
}
int getDataGameStarted(Data data)
{
    return data->gameStarted;
}