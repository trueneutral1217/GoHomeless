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

bool stage::loadStage(SDL_Renderer* renderer, bool success)
{
    setButtonNames();
    //load stage button textures and positions
    success = setStageButtonTextures(renderer,success);
    //set stage bg texture
    success = setStageTextures(renderer);
    //load player texture
    player1.loadPlayer(renderer);
    return success;
}

void stage::free()
{
    freeButtons();
    freeBGTextures();
    player1.freePlayer();
}

void stage::renderStage1(SDL_Renderer* renderer)
{
    stage1BG[0].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    player1.render(renderer);
    buttons[0].buttonTexture.render(buttons[0].getPositionX(),buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}
