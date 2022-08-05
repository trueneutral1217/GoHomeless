#include "stage.h"

stage::stage()
{

}

stage::~stage()
{

}

void stage::freeButtons()
{
    for(int i = 0; i < TOTAL_STAGE_BUTTONS; i++)
    {
        buttons[i].buttonTexture.free();
    }
}

bool stage::setStageButtonTextures(SDL_Renderer* renderer, bool success)
{
    for( int i = 0; i < TOTAL_STAGE_BUTTONS; ++i )
    {
        std::stringstream ss;
        ss << "images/buttons/" << buttons[i].buttonName << ".png";
        std::string str = ss.str();
        success = buttons[i].buttonTexture.loadFromFile( str,renderer );
        //buttons[ i ].setPosition( ((i*160)-80), SCREEN_HEIGHT - 140 );
    }
    //save and exit
    buttons[0].setPosition(600,20);
    return success;
}

void stage::setButtonNames()
{
    for(int i = 0; i < TOTAL_STAGE_BUTTONS; i++)
    {
        buttons[i].setStageButtonName(i);
    }
}

bool stage::setStageTextures(SDL_Renderer* renderer)
{
    bool success = true;
    setFileNames();
    for(int i = 0; i<TOTAL_STAGE_BACKGROUNDS;i++)
    {
        success = stage1BG[i].loadFromFile( bgFileName[i],renderer );
    }

    return success;
}

void stage::setFileNames()
{
    bgFileName[0] = "images/thanks.png";
}

void stage::freeBGTextures()
{
    stage1BG[0].free();
}
