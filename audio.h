#ifndef AUDIO_H
#define AUDIO_H

#include "texture.h"
#include <SDL_mixer.h>

const int TOTAL_SOUNDS = 4;

class audio
{
    public:

        Mix_Music *music;
        Mix_Chunk *sound;
        Mix_Chunk *voice;
        audio();
        ~audio();
        //music
        void loadMusic();
        void loadChapter1Music();
        void loadChapter2Music();
        void loadChapter3Music();
        //sounds
        void loadSound(int soundNum);
        void loadVoice(int chapter, int page,int line);

        void playMusic();
        void pauseMusic();
        void resumeMusic();
        void stopMusic();
        void playSound();
        void playVoice();
        void stopVoice();
        void freeAudio();



    private:

};
#endif // AUDIO_H
