#ifndef CHAPTER_H
#define CHAPTER_H

//#include "Texture.h"
//texture.h is included in button.h, so maybe I'm okay to exclude the line.
#include "timer.h"
#include "button.h"
#include "parallax.h"

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

        //timer for dialog for chapter1
        timer chapter1Timer;
        timer chapter2Timer;

        button buttons[TOTAL_CHAPTER_BUTTONS];

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
        Texture chapter2BG[TOTAL_PAGES];
        Texture dialogBox;
        Texture menuBar;

        parallax ch2Pg7Fore;
        parallax ch2Pg7Mid;
        parallax ch2Pg7Back;

        parallax ch2Pg8Fore;
        parallax ch2Pg8AnteriorMid;
        parallax ch2Pg8Mid;
        parallax ch2Pg8Back;

        void ch2Pg7handleParallax(SDL_Renderer* renderer);
        void ch2Pg8handleParallax(SDL_Renderer* renderer);

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
        std::string bgFileName2[TOTAL_PAGES];
        void freeBGTextures();
        //sets file names for page backgrounds
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

        void setAutoScript();

        //player clicks mouse button
        int progress(SDL_Renderer* renderer,int gameState);
        //player presses spacebar
        int progress2(SDL_Renderer* renderer,int gameState);
        //player presses h button
        void handleDialogVisability();
        //renders correct state of the visibility of dialog, dialog box.
        void handleDialogRendering(SDL_Renderer* renderer);
        //renders correct bg with it's corresponding page.
        void renderBackgrounds(SDL_Renderer* renderer,int j);
        //updates current page/script compensation
        void handleBackPagePress();
        //updates current line plus script compensation
        void handleBackLinePress();
        //sets buttonTexture by buttonName and position
        bool setChapterButtonTextures(SDL_Renderer* renderer, bool success);
        //set button names
        void setButtonNames();
        //free button textures at close time
        void freeButtons();
        //handles pretty much all rendering except animation in chapter 1
        void handleRendering(SDL_Renderer* renderer);
        //load savegame data into chapter variables
        void loadSavedVariables(Sint32 data0, Sint32 data1,Sint32 data2,Sint32 data3);

        int handleChapterButtonPresses(int gameState,SDL_Event* e, SDL_Window* window,SDL_Renderer* renderer );

    private:

};

#endif // CHAPTER_H
