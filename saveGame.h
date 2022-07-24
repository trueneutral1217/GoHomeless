#ifndef SAVEGAME_H
#define SAVEGAME_H

#include "Texture.h"

//total save game data point
const int TOTAL_DATA = 3;

class saveGame
{
    public:

    //file read/write stuff
    Sint32 gData[ TOTAL_DATA ];
    SDL_RWops* file = SDL_RWFromFile( "savegame/save.gsf", "r+b" );

    void readFile();
    void writeFile(int currentChapter,int currentPage,int currentScript);


    private:

};


#endif // SAVEGAME_H
