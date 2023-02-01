#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>
#include "bike.h"

typedef struct Client_type *Client;
typedef struct Data_type *Data;

#ifndef network_h
#define network_h

Client createClient();
Data createData();
Data createTmp();
void initNetwork(Client theClient, char ip[16]);
void sendRecv(Client theClient, Data data, int x, int y, int angle, int playerID, int alive, int gameStarted);
void closeTCPconnection(Client theClient);
void setID(Data data);
int getDatax(Data data, int i);
int getDatay(Data data, int i);
int getDataAngle(Data data, int i);
int getDataPlayerID(Data data, int i);
int getDataAlive(Data data, int i);
int getDataGameStarted(Data data);
#endif