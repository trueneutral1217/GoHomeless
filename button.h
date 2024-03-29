#ifndef BUTTON_H
#define BUTTON_H

#include "Texture.h"

//buttons on the title screen + back button for screens like options
const int TOTAL_BUTTONS = 15;

const int BUTTON_WIDTH = 160;
const int BUTTON_HEIGHT = 120;

//buttons in the menubar plus save & quit button .
const static int TOTAL_CHAPTER_BUTTONS=8;
//new game, load game, options, credits, back button, and fullscreen on/off button.
const static int TOTAL_PREGAME_BUTTONS = 8;
//gamestate=6, stage1 buttons
const static int TOTAL_STAGE_BUTTONS = 1;

class button
{
    public:
		//Initializes internal variables
		button();
        ~button();
		//Sets top left position
		void setPosition( int x, int y );

		int getPositionX();
		int getPositionY();
		bool fullScreen;

		//Handles mouse event
		int handleEvent( int gameState, std::string buttonName, SDL_Event* e, SDL_Window* window,SDL_Renderer* renderer );

        Texture buttonTexture;

        bool setFullScreenOn(SDL_Window* window,SDL_Renderer* renderer);
        bool setFullScreenOff(SDL_Window* window,SDL_Renderer* renderer);


		std::string buttonName;

		std::string pregameButtonNames[TOTAL_PREGAME_BUTTONS];
		std::string chapterButtonNames[TOTAL_CHAPTER_BUTTONS];
		std::string stageButtonNames[TOTAL_STAGE_BUTTONS];
        //each button has a string that describes the button.
		void setChapterButtonName(int i);
		void setPregameButtonName(int i);
		void setStageButtonName(int i);
		//determines which texture to show in options screen, red or green.
		void fullScreenButtonTextureToggle(SDL_Renderer* renderer);


	private:
		//Top left point of button image location
		SDL_Point position;

};

#endif // BUTTON_H
