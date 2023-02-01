#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "sound.h"
#include <stdbool.h>

struct Sound_type{
    Mix_Music *menuSound;
    Mix_Music *gameSound;

    Mix_Chunk *chrash;
};

Sound initSound()
{
    Sound t = malloc(sizeof(struct Sound_type));

    t->gameSound = Mix_LoadMUS( "beat.mp3" );
    if( t->gameSound == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    t->menuSound = Mix_LoadMUS( "Barbie.mp3" );
    if( t->menuSound == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    t->chrash = Mix_LoadWAV( "explode.wav" );
    if( t->chrash == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    return t;
}

void playSound(Sound theSound, bool *changeSong, int choose)
{
    if( *changeSong == true && choose == 0)
    {
        Mix_HaltMusic();
        Mix_PlayMusic( theSound->menuSound, -1 );
        *changeSong = false;
    }
    else if ( *changeSong == true && choose == 1)
    {
        Mix_HaltMusic();
        Mix_PlayMusic( theSound->gameSound, -1);
        *changeSong = false;
    }
}

void playSoundEffect(Sound theSound)
{
    Mix_PlayChannel( -1, theSound->chrash, 0 );
}

void freeSound(Sound theSound)
{
    Mix_FreeMusic(theSound->gameSound);
    theSound->gameSound = NULL;
    Mix_FreeMusic(theSound->menuSound);
    theSound->menuSound = NULL;
    Mix_FreeChunk(theSound->chrash);
    theSound->chrash = NULL;
}