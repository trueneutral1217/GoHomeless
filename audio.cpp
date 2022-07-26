#include "audio.h"

audio::audio()
{
    music = NULL;
    sound = NULL;
}
audio::~audio()
{
    //
    Mix_FreeMusic( music );
    Mix_FreeChunk( sound );
    sound=NULL;
    music=NULL;
}

void audio::loadMusic()
{
    music = Mix_LoadMUS( "music/Radioactive Rain.mp3" );
}

void audio::loadSound()
{
    sound = Mix_LoadWAV( "sounds/titleitemselect1.wav" );
}

void audio::playMusic()
{
    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic( music, -1 );
    }
    //If music is being played
    else
    {
        //If the music is paused
        if( Mix_PausedMusic() == 1 )
        {
            //Resume the music
            Mix_ResumeMusic();
        }
        //If the music is playing
        else
        {
            //Pause the music
            Mix_PauseMusic();
        }
    }
}
