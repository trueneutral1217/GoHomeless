#ifndef CHAPTER_H
#define CHAPTER_H

#include "Texture.h"

//number of dialog lines for chapter 1.
const int TOTAL_SCRIPTS = 8;
//number of dialog pages for chapter 1.
const int TOTAL_PAGES = 8;
//number of dialogs
const int TOTAL_CHAPTERS=2;

class chapter
{
    public:
        //constructor
        chapter();
        //destructor
        ~chapter();
        //declare font
        TTF_Font *font;

        //tracks chapter progress.  used to save/load and display properly
        int currentScript;
        int currentPage;
        int currentChapter;
        bool chapter1Complete;

        Texture scriptTexture[TOTAL_PAGES][TOTAL_SCRIPTS];
        Texture chapter1BG[TOTAL_PAGES];

        std::stringstream scriptString[TOTAL_PAGES][TOTAL_SCRIPTS];

        //Load Strings
        void loadChapterStrings(SDL_Renderer* renderer);

        void scriptIncrement();
        void pageIncrement();
        void backScript();
        void backPage();
        void completeChapter(SDL_Renderer* renderer);
        void resetChapters(SDL_Renderer* renderer);
        void resetPages();
        void resetScripts();

        void loadLineText(SDL_Renderer* renderer);
        void loadPageText(SDL_Renderer* renderer);

        //
        std::string bgFileName[TOTAL_PAGES];
        void freeBGTextures();
        void setFileNames();
        bool setScriptTextures(SDL_Renderer* renderer);
        bool setBGTextures(SDL_Renderer* renderer);
        void loadFont();

        std::stringstream pageText;
        std::stringstream lineText;
        Texture curLineTextTexture;
        Texture curPageTextTexture;



    private:

};

#endif // CHAPTER_H
