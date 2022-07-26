#ifndef BUTTON_H
#define BUTTON_H

#include "Texture.h"

//buttons on the title screen + back button for screens like options
const int TOTAL_BUTTONS = 7;

const int BUTTON_WIDTH = 160;
const int BUTTON_HEIGHT = 120;

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
		//int getWidth();
		//int getHeight();

		//Handles mouse event
		int handleEvent( int gameState, std::string buttonName, SDL_Event* e, SDL_Window* window );

        Texture buttonTexture;

        bool setFullScreenOn();
        bool setFullScreenOff();

		//void render(texture gButtonTexture,SDL_Renderer* gRenderer);

		std::string buttonName;

	private:
		//Top left point of button image location
		SDL_Point position;

};

#endif // BUTTON_H
