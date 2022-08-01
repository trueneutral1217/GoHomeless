#ifndef AUDIO_H
#define AUDIO_H

#include <SDL_mixer.h>

class audio
{
    public:

        Mix_Music *music;
        Mix_Chunk *sound;
        audio();
        ~audio();

        void loadMusic();
        void loadSound();
        void playMusic();
        void freeAudio();

    private:

};
#endif // AUDIO_H
