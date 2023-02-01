#ifndef sound_h
#define sound_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

typedef struct Sound_type *Sound;

Sound initSound();
void playSound(Sound theSound, bool *changeSong, int choose);
void playSoundEffect(Sound theSound);
void freeSound(Sound theSound);

#endif