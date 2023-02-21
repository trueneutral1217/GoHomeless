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

void audio::loadChapter1Music()
{
    music = Mix_LoadMUS("music/Meadow March.mp3");
}

void audio::loadChapter2Music()
{
    music = Mix_LoadMUS("music/Tiki Jungle.mp3");
}

void audio::loadSound(int soundNum)
{
    switch(soundNum)
    {
        case 0:
            sound = Mix_LoadWAV( "sounds/voice0.mp3" );
        break;
        case 1:
            sound = Mix_LoadWAV( "sounds/gem.mp3" );
        break;
        case 2:
            sound = Mix_LoadWAV( "sounds/shovel.mp3" );
        break;
        case 3:
            sound = Mix_LoadWAV( "sounds/titleitemselect4.wav" );
        break;
    }

}
void audio::freeAudio()
{
    Mix_FreeChunk( sound );
    sound = NULL;
    Mix_FreeMusic( music );
	music = NULL;
}

void audio::playSound()
{
    Mix_PlayChannel( -1, sound, 0 );
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

void audio::pauseMusic()
{
    Mix_PauseMusic();
}

void audio::resumeMusic()
{
    Mix_ResumeMusic();
}

void audio::stopMusic()
{
    Mix_HaltMusic();
}
