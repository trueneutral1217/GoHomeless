#ifndef SAVEGAME_H
#define SAVEGAME_H

#include "Texture.h"

//total save game data point
const int TOTAL_DATA = 4;

class saveGame
{
    public:

    //file read/write stuff
    Sint32 data[ TOTAL_DATA ];
    SDL_RWops* file = SDL_RWFromFile( "savegame/save.gsf", "r+b" );

    void readFile();
    void writeFile(int currentChapter,int currentPage,int currentScript, bool chapter1Complete);


    private:

};


#endif // SAVEGAME_H
