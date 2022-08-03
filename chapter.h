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
        bool autoText;
        int autoTextSpeed;

        //user presses 'h' to hide the dialogbox, or dialog box & text, or neither.
        bool hideDialogBox = false;
        bool hideDialogAndBox = false;
        bool fullScreen = false;

        Texture scriptTexture[TOTAL_PAGES][TOTAL_SCRIPTS];
        Texture chapter1BG[TOTAL_PAGES];
        Texture dialogBox;
        Texture menuBar;

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
        bool setChapterTextures(SDL_Renderer* renderer);
        void loadFont();

        std::stringstream pageText;
        std::stringstream lineText;
        Texture curLineTextTexture;
        Texture curPageTextTexture;
        //tests savegame variables, usually when altered, saved, or loaded.
        void testSaveVariables();


    private:

};

#endif // CHAPTER_H
