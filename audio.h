#ifndef AUDIO_H
#define AUDIO_H

#include <SDL_mixer.h>

const int TOTAL_SOUNDS = 4;

class audio
{
    public:

        Mix_Music *music;
        Mix_Chunk *sound;
        audio();
        ~audio();

        void loadMusic();
        void loadSound(int soundNum);
        void playMusic();
        void playSound();
        void freeAudio();

    private:

};
#endif // AUDIO_H
