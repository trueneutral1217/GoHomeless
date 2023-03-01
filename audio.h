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
        void loadChapter1Music();
        void loadChapter2Music();
        void loadChapter3Music();
        void loadSound(int soundNum);
        void playMusic();
        void pauseMusic();
        void resumeMusic();
        void stopMusic();
        void playSound();
        void freeAudio();

    private:

};
#endif // AUDIO_H
