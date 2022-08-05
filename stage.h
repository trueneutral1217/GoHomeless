#ifndef STAGE_H
#define STAGE_H

#include "Texture.h"
//#include "timer.h"
#include "button.h"
#include "player.h"

const static int TOTAL_STAGE_BACKGROUNDS = 1;

class stage
{
    public:
        //constructor
        stage();
        //destructor
        ~stage();

        Texture thanksTexture;

        button buttons[TOTAL_STAGE_BUTTONS];

        std::string bgFileName[TOTAL_STAGE_BACKGROUNDS];

        Texture stage1BG[TOTAL_STAGE_BACKGROUNDS];

        void freeButtons();

        void freeBGTextures();

        bool setStageButtonTextures(SDL_Renderer* renderer, bool success);

        bool setStageTextures(SDL_Renderer* renderer);

        void setFileNames();

        //set button names
        void setButtonNames();

        //declare player
        player player1;

    private:

};

#endif // STAGE_H
